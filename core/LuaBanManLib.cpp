/*
 * PtokaX - hub server for Direct Connect peer to peer network.

 * Copyright (C) 2002-2005  Ptaczek, Ptaczek at PtokaX dot org
 * Copyright (C) 2004-2010  Petr Kozelka, PPK at PtokaX dot org

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
#include "stdinc.h"
//---------------------------------------------------------------------------
#include "LuaInc.h"
//---------------------------------------------------------------------------
#include "LuaBanManLib.h"
//---------------------------------------------------------------------------
#include "hashBanManager.h"
#include "hashUsrManager.h"
#include "LuaScriptManager.h"
#include "UdpDebug.h"
#include "User.h"
#include "utility.h"
//---------------------------------------------------------------------------
#ifdef _WIN32
	#pragma hdrstop
#endif
//---------------------------------------------------------------------------
#include "LuaScript.h"
//---------------------------------------------------------------------------
#ifdef _WIN32
	#ifndef _MSC_VER
		#pragma package(smart_init)
	#endif
#endif
//---------------------------------------------------------------------------

static void PushBan(lua_State * L, BanItem * b) {
	lua_checkstack(L, 3); // we need 3 (1 table, 2 id, 3 value) empty slots in stack, check it to be sure

	lua_newtable(L);
	int i = lua_gettop(L);

    lua_pushliteral(L, "sIP");
    if(b->sIp[0] == '\0') {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, b->sIp);
	}
    lua_rawset(L, i);

    lua_pushliteral(L, "sNick");
    if(b->sNick == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, b->sNick);
	}
    lua_rawset(L, i);

    lua_pushliteral(L, "sReason");
    if(b->sReason == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, b->sReason);
	}
    lua_rawset(L, i);

    lua_pushliteral(L, "sBy");
    if(b->sBy == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, b->sBy);
	}
    lua_rawset(L, i);

    lua_pushliteral(L, "iExpireTime");
    ((b->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == false ? lua_pushnil(L) : lua_pushnumber(L, (double)b->tempbanexpire);
    lua_rawset(L, i);

    lua_pushliteral(L, "bIpBan");
    ((b->ui8Bits & hashBanMan::IP) == hashBanMan::IP) == true ? lua_pushboolean(L, 1) : lua_pushnil(L);
    lua_rawset(L, i);

    lua_pushliteral(L, "bNickBan");
    ((b->ui8Bits & hashBanMan::NICK) == hashBanMan::NICK) == true ? lua_pushboolean(L, 1) : lua_pushnil(L);
    lua_rawset(L, i);

    lua_pushliteral(L, "bFullIpBan");
    ((b->ui8Bits & hashBanMan::FULL) == hashBanMan::FULL) == true ? lua_pushboolean(L, 1) : lua_pushnil(L);
    lua_rawset(L, i);
}
//------------------------------------------------------------------------------

static void PushRangeBan(lua_State * L, RangeBanItem * rb) {
	lua_checkstack(L, 3); // we need 3 (1 table, 2 id, 3 value) empty slots in stack, check it to be sure

	lua_newtable(L);
	int i = lua_gettop(L);

    lua_pushliteral(L, "sIPFrom");
    lua_pushstring(L, rb->sIpFrom);
    lua_rawset(L, i);

    lua_pushliteral(L, "sIPTo");
    lua_pushstring(L, rb->sIpTo);
    lua_rawset(L, i);

    lua_pushliteral(L, "sReason");
    if(rb->sReason == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, rb->sReason);
	}
    lua_rawset(L, i);

    lua_pushliteral(L, "sBy");
    if(rb->sBy == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, rb->sBy);
	}
    lua_rawset(L, i);

    lua_pushliteral(L, "iExpireTime");
    ((rb->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == false ? lua_pushnil(L) : lua_pushnumber(L, (double)rb->tempbanexpire);
    lua_rawset(L, i);

    lua_pushliteral(L, "bFullIpBan");
    ((rb->ui8Bits & hashBanMan::FULL) == hashBanMan::FULL) == true ? lua_pushboolean(L, 1) : lua_pushnil(L);
    lua_rawset(L, i);
}
//------------------------------------------------------------------------------

static int Save(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'Save' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        return 0;
    }

	hashBanManager->Save(true);

    return 0;
}
//------------------------------------------------------------------------------

static int GetBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'GetBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    lua_newtable(L);
    int t = lua_gettop(L), i = 0;

    time_t acc_time;
    time(&acc_time);

    BanItem *nextBan = hashBanManager->TempBanListS;

    while(nextBan != NULL) {
        BanItem *curBan = nextBan;
		nextBan = curBan->next;

        if(acc_time > curBan->tempbanexpire) {
			hashBanManager->Rem(curBan);
            delete curBan;

			continue;
        }

        lua_pushnumber(L, ++i);
        PushBan(L, curBan);        
        lua_rawset(L, t);
    }

	nextBan = hashBanManager->PermBanListS;

    while(nextBan != NULL) {
        BanItem *curBan = nextBan;
		nextBan = curBan->next;

        lua_pushnumber(L, ++i);
        PushBan(L, curBan);        
        lua_rawset(L, t);
    }

    return 1;
}
//---------------------------------------------------------------------------

static int GetTempBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'GetTempBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    lua_newtable(L);
    int t = lua_gettop(L), i = 0;

    time_t acc_time;
    time(&acc_time);

    BanItem *nextBan = hashBanManager->TempBanListS;

    while(nextBan != NULL) {
        BanItem *curBan = nextBan;
		nextBan = curBan->next;

        if(acc_time > curBan->tempbanexpire) {
			hashBanManager->Rem(curBan);
            delete curBan;

			continue;
        }

        lua_pushnumber(L, ++i);
        PushBan(L, curBan);        
        lua_rawset(L, t);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int GetPermBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'GetPermBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    lua_newtable(L);
    int t = lua_gettop(L), i = 0;

	BanItem *nextBan = hashBanManager->PermBanListS;

    while(nextBan != NULL) {
        BanItem *curBan = nextBan;
		nextBan = curBan->next;

        lua_pushnumber(L, ++i);
        PushBan(L, curBan);        
        lua_rawset(L, t);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int GetBan(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'GetBan' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    time_t acc_time;
    time(&acc_time);

    size_t iLen;
    char *sValue = (char *)lua_tolstring(L, 1, &iLen);

    uint32_t hash;

	BanItem *Ban = hashBanManager->FindNick(sValue, iLen);

	if(HashIP(sValue, iLen, hash) == true) {
        lua_settop(L, 0);
        
        lua_newtable(L);
        int t = lua_gettop(L), i = 0;

        if(Ban != NULL) {
            lua_pushnumber(L, ++i);
            PushBan(L, Ban); 
            lua_rawset(L, t);
        }

		Ban = hashBanManager->FindIP(hash, acc_time);
        if(Ban != NULL) {
            lua_pushnumber(L, ++i);
            PushBan(L, Ban);        
            lua_rawset(L, t);

            BanItem *nextBan = Ban->hashiptablenext;
        
            while(nextBan != NULL) {
                BanItem *curBan = nextBan;
				nextBan = curBan->hashiptablenext;

				if((((curBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == true) && acc_time > curBan->tempbanexpire) {
					hashBanManager->Rem(curBan);
                    delete curBan;

        			continue;
                }

                lua_pushnumber(L, ++i);
                PushBan(L, curBan);        
                lua_rawset(L, t);
            }
        }
        return 1;
    } else {
        lua_settop(L, 0);

        if(Ban == NULL) {
        	lua_pushnil(L);
            return 1;
        }

        PushBan(L, Ban); 
        return 1;
    }
}
//------------------------------------------------------------------------------

static int GetPermBan(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'GetPermBan' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iLen;
    char *sValue = (char *)lua_tolstring(L, 1, &iLen);

    uint32_t hash;

	BanItem *Ban = hashBanManager->FindPermNick(sValue, iLen);

    if(HashIP(sValue, iLen, hash) == true) {
        lua_settop(L, 0);
        
        lua_newtable(L);
        int t = lua_gettop(L), i = 0;

        if(Ban != NULL) {
            lua_pushnumber(L, ++i);
            PushBan(L, Ban); 
            lua_rawset(L, t);
        }

		Ban = hashBanManager->FindPermIP(hash);
        if(Ban != NULL) {
            lua_pushnumber(L, ++i);
            PushBan(L, Ban);        
            lua_rawset(L, t);

            BanItem *nextBan = Ban->hashiptablenext;
        
            while(nextBan != NULL) {
                BanItem *curBan = nextBan;
        		nextBan = curBan->hashiptablenext;

				if(((curBan->ui8Bits & hashBanMan::PERM) == hashBanMan::PERM) == false) {
        			continue;
                }

                lua_pushnumber(L, ++i);
                PushBan(L, curBan);        
                lua_rawset(L, t);
            }
        }
        return 1;
    } else {
        lua_settop(L, 0);

        if(Ban == NULL) {
        	lua_pushnil(L);
            return 1;
        }

        PushBan(L, Ban); 
        return 1;
    }
}
//------------------------------------------------------------------------------

static int GetTempBan(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'GetTempBan' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    time_t acc_time;
    time(&acc_time);

    size_t iLen;
    char *sValue = (char *)lua_tolstring(L, 1, &iLen);

    uint32_t hash;

	BanItem *Ban = hashBanManager->FindTempNick(sValue, iLen);

    if(HashIP(sValue, iLen, hash) == true) {
        lua_settop(L, 0);
        
        lua_newtable(L);
        int t = lua_gettop(L), i = 0;

        if(Ban != NULL) {
            lua_pushnumber(L, ++i);
            PushBan(L, Ban); 
            lua_rawset(L, t);
        }

		Ban = hashBanManager->FindTempIP(hash, acc_time);
        if(Ban != NULL) {
            lua_pushnumber(L, ++i);
            PushBan(L, Ban);        
            lua_rawset(L, t);

            BanItem *nextBan = Ban->hashiptablenext;
        
            while(nextBan != NULL) {
                BanItem *curBan = nextBan;
        		nextBan = curBan->hashiptablenext;

				if(((curBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == true) {
                    if(acc_time > curBan->tempbanexpire) {
						hashBanManager->Rem(curBan);
                        delete curBan;
    
            			continue;
                    }

                    lua_pushnumber(L, ++i);
                    PushBan(L, curBan);        
                    lua_rawset(L, t);
                }
            }
        }
        return 1;
    } else {
        lua_settop(L, 0);

        if(Ban == NULL) {
        	lua_pushnil(L);
            return 1;
        }

        PushBan(L, Ban); 
        return 1;
    }
}
//------------------------------------------------------------------------------

static int GetRangeBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'GetRangeBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }
    
    lua_newtable(L);
	int t = lua_gettop(L), i = 0;

    time_t acc_time;
    time(&acc_time);

    RangeBanItem *nextBan = hashBanManager->RangeBanListS;

    while(nextBan != NULL) {
        RangeBanItem *curBan = nextBan;
		nextBan = curBan->next;
        
        if((((curBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == true) && acc_time > curBan->tempbanexpire) {
			hashBanManager->RemRange(curBan);
            delete curBan;

			continue;
        }

        lua_pushnumber(L, ++i);
        PushRangeBan(L, curBan);
        lua_rawset(L, t);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int GetTempRangeBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'GetTempRangeBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }
    
    lua_newtable(L);
	int t = lua_gettop(L), i = 0;

    time_t acc_time;
    time(&acc_time);

    RangeBanItem *nextBan = hashBanManager->RangeBanListS;

    while(nextBan != NULL) {
        RangeBanItem *curBan = nextBan;
		nextBan = curBan->next;

        if(((curBan->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == false) {
            continue;
        }
        
        if(acc_time > curBan->tempbanexpire) {
			hashBanManager->RemRange(curBan);
            delete curBan;

			continue;
        }

        lua_pushnumber(L, ++i);
        PushRangeBan(L, curBan);
        lua_rawset(L, t);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int GetPermRangeBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'GetPermRangeBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }
    
    lua_newtable(L);
	int t = lua_gettop(L), i = 0;

    RangeBanItem *nextBan = hashBanManager->RangeBanListS;

    while(nextBan != NULL) {
        RangeBanItem *curBan = nextBan;
		nextBan = curBan->next;

        if(((curBan->ui8Bits & hashBanMan::PERM) == hashBanMan::PERM) == false) {
            continue;
        }
        
        lua_pushnumber(L, ++i);
        PushRangeBan(L, curBan);
        lua_rawset(L, t);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int GetRangeBan(lua_State * L) {
	if(lua_gettop(L) != 2) {
        luaL_error(L, "bad argument count to 'GetRangeBan' (2 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromLen, iToLen;
    char *sFrom = (char *)lua_tolstring(L, 1, &iFromLen);
    char *sTo = (char *)lua_tolstring(L, 2, &iToLen);

	uint32_t fromhash, tohash;

    if(iFromLen == 0 || iToLen == 0 ||HashIP(sFrom, iFromLen, fromhash) == false || HashIP(sTo, iToLen, tohash) == false || tohash <= fromhash) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    lua_settop(L, 0);

    time_t acc_time;
    time(&acc_time);

	RangeBanItem *next = hashBanManager->RangeBanListS;

    while(next != NULL) {
        RangeBanItem *cur = next;
        next = cur->next;

        if(cur->ui32FromIpHash == fromhash && cur->ui32ToIpHash == tohash) {
            // PPK ... check if it's temban and then if it's expired
            if(((cur->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == true) {
                if(acc_time >= cur->tempbanexpire) {
					hashBanManager->RemRange(cur);
                    delete cur;

					continue;
                }
            }
            PushRangeBan(L, cur);
            return 1;
        }
    }

	lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int GetRangePermBan(lua_State * L) {
	if(lua_gettop(L) != 2) {
        luaL_error(L, "bad argument count to 'GetRangePermBan' (2 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromLen, iToLen;
    char *sFrom = (char *)lua_tolstring(L, 1, &iFromLen);
    char *sTo = (char *)lua_tolstring(L, 2, &iToLen);

	uint32_t fromhash, tohash;

	if(iFromLen == 0 || iToLen == 0 ||HashIP(sFrom, iFromLen, fromhash) == false || HashIP(sTo, iToLen, tohash) == false || tohash <= fromhash) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    lua_settop(L, 0);

    RangeBanItem *next = hashBanManager->RangeBanListS;

    while(next != NULL) {
        RangeBanItem *cur = next;
        next = cur->next;

        if(cur->ui32FromIpHash == fromhash && cur->ui32ToIpHash == tohash) {
            if(((cur->ui8Bits & hashBanMan::PERM) == hashBanMan::PERM) == true) {
                PushRangeBan(L, cur);
                return 1;
            }
        }
    }

	lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int GetRangeTempBan(lua_State * L) {
	if(lua_gettop(L) != 2) {
        luaL_error(L, "bad argument count to 'GetRangeTempBan' (2 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromLen, iToLen;
    char *sFrom = (char *)lua_tolstring(L, 1, &iFromLen);
    char *sTo = (char *)lua_tolstring(L, 2, &iToLen);

	uint32_t fromhash, tohash;

	if(iFromLen == 0 || iToLen == 0 ||HashIP(sFrom, iFromLen, fromhash) == false || HashIP(sTo, iToLen, tohash) == false || tohash <= fromhash) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    lua_settop(L, 0);

    time_t acc_time;
    time(&acc_time);

    RangeBanItem *next = hashBanManager->RangeBanListS;

    while(next != NULL) {
        RangeBanItem *cur = next;
        next = cur->next;

        if(cur->ui32FromIpHash == fromhash && cur->ui32ToIpHash == tohash) {
            // PPK ... check if it's temban and then if it's expired
            if(((cur->ui8Bits & hashBanMan::TEMP) == hashBanMan::TEMP) == true) {
                if(acc_time >= cur->tempbanexpire) {
					hashBanManager->RemRange(cur);
                    delete cur;

					continue;
                }

                PushRangeBan(L, cur);
                return 1;
            }
        }
    }

	lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int Unban(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'Unban' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iLen;
    char *sWhat = (char *)lua_tolstring(L, 1, &iLen);

    if(iLen == 0) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }
    
    if(hashBanManager->Unban(sWhat) == false) {
        lua_settop(L, 0);
        lua_pushnil(L);
    } else {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int UnbanPerm(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'UnbanPerm' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iLen;
    char *sWhat = (char *)lua_tolstring(L, 1, &iLen);

    if(iLen == 0) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }
    
    if(hashBanManager->PermUnban(sWhat) == false) {
        lua_settop(L, 0);
        lua_pushnil(L);
    } else {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int UnbanTemp(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'UnbanTemp' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iLen;
    char *sWhat = (char *)lua_tolstring(L, 1, &iLen);

    if(iLen == 0) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }
    
    if(hashBanManager->TempUnban(sWhat) == false) {
        lua_settop(L, 0);
        lua_pushnil(L);
    } else {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int UnbanAll(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'UnbanAll' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        return 0;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
        return 0;
    }

    size_t iLen;
    char *sIP = (char *)lua_tolstring(L, 1, &iLen);

    uint32_t hash;

    if(iLen == 0 || HashIP(sIP, iLen, hash) == false) {
		lua_settop(L, 0);
        return 0;
    }

    lua_settop(L, 0);

	hashBanManager->RemoveAllIP(hash);

    return 0;
}
//------------------------------------------------------------------------------

static int UnbanPermAll(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'UnbanPermAll' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        return 0;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
        return 0;
    }

    size_t iLen;
    char *sIP = (char *)lua_tolstring(L, 1, &iLen);

    uint32_t hash;

    if(iLen == 0 || HashIP(sIP, iLen, hash) == false) {
		lua_settop(L, 0);
        return 0;
    }

    lua_settop(L, 0);

	hashBanManager->RemovePermAllIP(hash);

    return 0;
}
//------------------------------------------------------------------------------

static int UnbanTempAll(lua_State * L) {
	if(lua_gettop(L) != 1) {
        luaL_error(L, "bad argument count to 'UnbanTempAll' (1 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        return 0;
    }

    if(lua_type(L, 1) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
		lua_settop(L, 0);
        return 0;
    }

    size_t iLen;
    char *sIP = (char *)lua_tolstring(L, 1, &iLen);

    uint32_t hash;

    if(iLen == 0 || HashIP(sIP, iLen, hash) == false) {
		lua_settop(L, 0);
        return 0;
    }

    lua_settop(L, 0);

	hashBanManager->RemoveTempAllIP(hash);

    return 0;
}
//------------------------------------------------------------------------------

static int RangeUnban(lua_State * L) {
	if(lua_gettop(L) != 2) {
        luaL_error(L, "bad argument count to 'RangeUnban' (2 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromIpLen, iToIpLen;
    char *sFromIp = (char *)lua_tolstring(L, 1, &iFromIpLen);
    char *sToIp = (char *)lua_tolstring(L, 2, &iToIpLen);

	uint32_t fromhash, tohash;

	if(iFromIpLen != 0 && iToIpLen != 0 && HashIP(sFromIp, iFromIpLen, fromhash) == true &&
        HashIP(sToIp, iToIpLen, tohash) == true && tohash > fromhash && hashBanManager->RangeUnban(fromhash, tohash) == true) {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
        return 1;
    }

    lua_settop(L, 0);
    lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int RangeUnbanPerm(lua_State * L) {
	if(lua_gettop(L) != 2) {
        luaL_error(L, "bad argument count to 'RangeUnbanPerm' (2 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromIpLen, iToIpLen;
    char *sFromIp = (char *)lua_tolstring(L, 1, &iFromIpLen);
    char *sToIp = (char *)lua_tolstring(L, 2, &iToIpLen);

	uint32_t fromhash, tohash;

	if(iFromIpLen != 0 && iToIpLen != 0 && HashIP(sFromIp, iFromIpLen, fromhash) == true &&
        HashIP(sToIp, iToIpLen, tohash) == true && tohash > fromhash && hashBanManager->RangeUnban(fromhash, tohash, hashBanMan::PERM) == true) {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
        return 1;
    }

    lua_settop(L, 0);
    lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int RangeUnbanTemp(lua_State * L) {
	if(lua_gettop(L) != 2) {
        luaL_error(L, "bad argument count to 'RangeUnbanTemp' (2 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromIpLen, iToIpLen;
    char *sFromIp = (char *)lua_tolstring(L, 1, &iFromIpLen);
    char *sToIp = (char *)lua_tolstring(L, 2, &iToIpLen);

	uint32_t fromhash, tohash;

	if(iFromIpLen != 0 && iToIpLen != 0 && HashIP(sFromIp, iFromIpLen, fromhash) == true &&
        HashIP(sToIp, iToIpLen, tohash) == true && tohash > fromhash && hashBanManager->RangeUnban(fromhash, tohash, hashBanMan::TEMP) == true) {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
        return 1;
    }

    lua_settop(L, 0);
    lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int ClearBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'ClearBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

	hashBanManager->ClearTemp();
	hashBanManager->ClearPerm();

    return 0;
}
//------------------------------------------------------------------------------

static int ClearPermBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'ClearPermBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

	hashBanManager->ClearPerm();

    return 0;
}
//------------------------------------------------------------------------------

static int ClearTempBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'ClearTempBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

	hashBanManager->ClearTemp();

    return 0;
}
//------------------------------------------------------------------------------

static int ClearRangeBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'ClearRangeBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

	hashBanManager->ClearRange();

    return 0;
}
//------------------------------------------------------------------------------

static int ClearRangePermBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'ClearRangePermBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

	hashBanManager->ClearPermRange();

    return 0;
}
//------------------------------------------------------------------------------

static int ClearRangeTempBans(lua_State * L) {
	if(lua_gettop(L) != 0) {
        luaL_error(L, "bad argument count to 'ClearRangeTempBans' (0 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    hashBanManager->ClearTempRange();

    return 0;
}
//------------------------------------------------------------------------------

static int Ban(lua_State * L) {
	if(lua_gettop(L) != 4) {
        luaL_error(L, "bad argument count to 'Ban' (4 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TTABLE || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TSTRING || lua_type(L, 4) != LUA_TBOOLEAN) {
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TSTRING);
        luaL_checktype(L, 3, LUA_TSTRING);
        luaL_checktype(L, 4, LUA_TBOOLEAN);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    User *u = ScriptGetUser(L, 4, "Ban");
                
    if(u == NULL) {
		lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 2, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

	size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 3, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    bool bFull = lua_toboolean(L, 4) == 0 ? false : true;

    hashBanManager->Ban(u, sReason, sBy, bFull);

    int imsgLen = sprintf(ScriptManager->lua_msg, "[SYS] User %s (%s) banned by script.", u->Nick, u->IP);
    if(CheckSprintf(imsgLen, 131072, "Ban") == true) {
        UdpDebug->Broadcast(ScriptManager->lua_msg, imsgLen);
    }

    UserClose(u);

    lua_settop(L, 0);
    lua_pushboolean(L, 1);
    return 1;
}
//------------------------------------------------------------------------------

static int BanIP(lua_State * L) {
	if(lua_gettop(L) != 4) {
        luaL_error(L, "bad argument count to 'Ban' (4 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TSTRING || lua_type(L, 4) != LUA_TBOOLEAN) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
        luaL_checktype(L, 3, LUA_TSTRING);
        luaL_checktype(L, 4, LUA_TBOOLEAN);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iIpLen;
    char *sIP = (char *)lua_tolstring(L, 1, &iIpLen);
    if(iIpLen == 0) {
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 2, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

    size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 3, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    bool bFull = lua_toboolean(L, 4) == 0 ? false : true;

    if(hashBanManager->BanIp(NULL, sIP, sReason, sBy, bFull) == 0) {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
    } else {
        lua_settop(L, 0);
        lua_pushnil(L);
    }

    return 1;
}
//------------------------------------------------------------------------------

static int BanNick(lua_State * L) {
	if(lua_gettop(L) != 3) {
        luaL_error(L, "bad argument count to 'BanNick' (3 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
        luaL_checktype(L, 3, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iNickLen;
    char *sNick = (char *)lua_tolstring(L, 1, &iNickLen);
    if(iNickLen == 0) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 2, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

    size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 3, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    User *curUser = hashManager->FindUser(sNick, iNickLen);
    if(curUser != NULL) {
        if(hashBanManager->NickBan(curUser, NULL, sReason, sBy) == true) {
            int imsgLen = sprintf(ScriptManager->lua_msg, "[SYS] User %s (%s) nickbanned by script.", curUser->Nick, curUser->IP);
            if(CheckSprintf(imsgLen, 131072, "NickBan") == true) {
                UdpDebug->Broadcast(ScriptManager->lua_msg, imsgLen);
            }
            UserClose(curUser);
            lua_pushboolean(L, 1);
        } else {
            UserClose(curUser);
            lua_pushnil(L);
        }
    } else {
        if(hashBanManager->NickBan(NULL, sNick, sReason, sBy) == true) {
            int imsgLen = sprintf(ScriptManager->lua_msg, "[SYS] Nick %s nickbanned by script.", sNick);
            if(CheckSprintf(imsgLen, 131072, "NickBan1") == true) {
                UdpDebug->Broadcast(ScriptManager->lua_msg, imsgLen);
            }
            lua_pushboolean(L, 1);
        } else {
            lua_pushnil(L);
        }
    }

    return 1;
}
//------------------------------------------------------------------------------

static int TempBan(lua_State * L) {
	if(lua_gettop(L) != 5) {
        luaL_error(L, "bad argument count to 'TempBan' (5 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TTABLE || lua_type(L, 2) != LUA_TNUMBER || lua_type(L, 3) != LUA_TSTRING || 
        lua_type(L, 4) != LUA_TSTRING || lua_type(L, 5) != LUA_TBOOLEAN) {
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TNUMBER);
        luaL_checktype(L, 3, LUA_TSTRING);
        luaL_checktype(L, 4, LUA_TSTRING);
        luaL_checktype(L, 5, LUA_TBOOLEAN);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    User *u = ScriptGetUser(L, 5, "TempBan");

    if(u == NULL) {
		lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

	uint32_t iMinutes = (uint32_t)lua_tonumber(L, 2);

	size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 3, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

	size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 4, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    bool bFull = lua_toboolean(L, 5) == 0 ? false : true;

    hashBanManager->TempBan(u, sReason, sBy, iMinutes, 0, bFull);

    int imsgLen = sprintf(ScriptManager->lua_msg, "[SYS] User %s (%s) tempbanned by script.", u->Nick, u->IP);
    if(CheckSprintf(imsgLen, 131072, "TempBan2") == true) {
        UdpDebug->Broadcast(ScriptManager->lua_msg, imsgLen);
    }

    UserClose(u);

    lua_settop(L, 0);
    lua_pushboolean(L, 1);
    return 1;
}
//------------------------------------------------------------------------------

static int TempBanIP(lua_State * L) {
	if(lua_gettop(L) != 5) {
        luaL_error(L, "bad argument count to 'TempBanIP' (5 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TNUMBER || lua_type(L, 3) != LUA_TSTRING || 
        lua_type(L, 4) != LUA_TSTRING || lua_type(L, 5) != LUA_TBOOLEAN) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TNUMBER);
        luaL_checktype(L, 3, LUA_TSTRING);
        luaL_checktype(L, 4, LUA_TSTRING);
        luaL_checktype(L, 5, LUA_TBOOLEAN);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iIpLen;
    char *sIP = (char *)lua_tolstring(L, 1, &iIpLen);
    if(iIpLen == 0) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

	uint32_t iMinutes = (uint32_t)lua_tonumber(L, 2);

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 3, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

    size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 4, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    bool bFull = lua_toboolean(L, 5) == 0 ? false : true;

    if(hashBanManager->TempBanIp(NULL, sIP, sReason, sBy, iMinutes, 0, bFull) == 0) {
        lua_settop(L, 0);
        lua_pushboolean(L, 1);
    } else {
        lua_settop(L, 0);
        lua_pushnil(L);
    }

    return 1;
}
//------------------------------------------------------------------------------
// NickTempBan(Nick, iTime, sReason, sBy) and user:NickTempBan(iTime, sReason, sBy)
static int TempBanNick(lua_State * L) {
	if(lua_gettop(L) != 4) {
        luaL_error(L, "bad argument count to 'TempBanNick' (4 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TNUMBER || lua_type(L, 3) != LUA_TSTRING || lua_type(L, 4) != LUA_TSTRING) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TNUMBER);
        luaL_checktype(L, 3, LUA_TSTRING);
        luaL_checktype(L, 4, LUA_TSTRING);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iNickLen;
    char *sNick = (char *)lua_tolstring(L, 1, &iNickLen);
    if(iNickLen == 0) {
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

	uint32_t iMinutes = (uint32_t)lua_tonumber(L, 2);

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 3, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

    size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 4, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    User *curUser = hashManager->FindUser(sNick, iNickLen);
    if(curUser != NULL) {
        if(hashBanManager->NickTempBan(curUser, NULL, sReason, sBy, iMinutes, 0) == true) {
            int imsgLen = sprintf(ScriptManager->lua_msg, "[SYS] User %s (%s) nickbanned by script.", curUser->Nick, curUser->IP);
            if(CheckSprintf(imsgLen, 131072, "NickTempBan2") == true) {
                UdpDebug->Broadcast(ScriptManager->lua_msg, imsgLen);
            }
            UserClose(curUser);
            lua_pushboolean(L, 1);
        } else {
            UserClose(curUser);
            lua_pushnil(L);
        }
    } else {
        if(hashBanManager->NickTempBan(NULL, sNick, sReason, sBy, iMinutes, 0) == true) {
            int imsgLen = sprintf(ScriptManager->lua_msg, "[SYS] Nick %s nickbanned by script.", sNick);
            if(CheckSprintf(imsgLen, 131072, "NickTempBan3") == true) {
                UdpDebug->Broadcast(ScriptManager->lua_msg, imsgLen);
            }
            lua_pushboolean(L, 1);
        } else {
            lua_pushnil(L);
        }
    }

    return 1;
}
//------------------------------------------------------------------------------

static int RangeBan(lua_State * L) {
	if(lua_gettop(L) != 5) {
        luaL_error(L, "bad argument count to 'RangeBan' (5 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TSTRING || 
        lua_type(L, 4) != LUA_TSTRING || lua_type(L, 5) != LUA_TBOOLEAN) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
        luaL_checktype(L, 3, LUA_TSTRING);
        luaL_checktype(L, 4, LUA_TSTRING);
        luaL_checktype(L, 5, LUA_TBOOLEAN);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromIpLen;
    char *sFromIP = (char *)lua_tolstring(L, 1, &iFromIpLen);

    size_t iToIpLen;
    char *sToIP = (char *)lua_tolstring(L, 2, &iToIpLen);

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 3, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

    size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 4, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    bool bFull = lua_toboolean(L, 5) == 0 ? false : true;

	uint32_t fromhash, tohash;

	if(iFromIpLen != 0 && iToIpLen != 0 && HashIP(sFromIP, iFromIpLen, fromhash) == true && HashIP(sToIP, iToIpLen, tohash) == true &&
        tohash > fromhash && hashBanManager->RangeBan(sFromIP, fromhash, sToIP, tohash, sReason, sBy, bFull) == true) {
		lua_settop(L, 0);
		lua_pushboolean(L, 1);
        return 1;
    }

	lua_settop(L, 0);
	lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static int RangeTempBan(lua_State * L) {
	if(lua_gettop(L) != 6) {
        luaL_error(L, "bad argument count to 'RangeTempBan' (6 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }

    if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TNUMBER || 
        lua_type(L, 4) != LUA_TSTRING || lua_type(L, 5) != LUA_TSTRING || lua_type(L, 6) != LUA_TBOOLEAN) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);
        luaL_checktype(L, 3, LUA_TNUMBER);
        luaL_checktype(L, 4, LUA_TSTRING);
        luaL_checktype(L, 5, LUA_TSTRING);
        luaL_checktype(L, 6, LUA_TBOOLEAN);
		lua_settop(L, 0);
		lua_pushnil(L);
        return 1;
    }

    size_t iFromIpLen;
    char *sFromIP = (char *)lua_tolstring(L, 1, &iFromIpLen);

    size_t iToIpLen;
    char *sToIP = (char *)lua_tolstring(L, 2, &iToIpLen);

    uint32_t iMinutes = (uint32_t)lua_tonumber(L, 3);

    size_t iReasonLen;
    char *sReason = (char *)lua_tolstring(L, 4, &iReasonLen);
    if(iReasonLen == 0) {
        sReason = NULL;
    }

    size_t iByLen;
    char *sBy = (char *)lua_tolstring(L, 5, &iByLen);
    if(iByLen == 0) {
        sBy = NULL;
    }

    bool bFull = lua_toboolean(L, 6) == 0 ? false : true;

    uint32_t fromhash, tohash;

	if(iFromIpLen != 0 && iToIpLen != 0 && HashIP(sFromIP, iFromIpLen, fromhash) == true && HashIP(sToIP, iToIpLen, tohash) == true &&
         tohash > fromhash && hashBanManager->RangeTempBan(sFromIP, fromhash, sToIP, tohash, sReason, sBy, iMinutes, 0, bFull) == true) {
		lua_settop(L, 0);
		lua_pushboolean(L, 1);
        return 1;
    }

	lua_settop(L, 0);
	lua_pushnil(L);
    return 1;
}
//------------------------------------------------------------------------------

static const luaL_reg banman_funcs[] =  {
    { "Save", Save }, 
	{ "GetBans", GetBans }, 
	{ "GetTempBans", GetTempBans }, 
	{ "GetPermBans", GetPermBans }, 
	{ "GetBan", GetBan }, 
	{ "GetPermBan", GetPermBan }, 
	{ "GetTempBan", GetTempBan }, 
	{ "GetRangeBans", GetRangeBans }, 
	{ "GetTempRangeBans", GetTempRangeBans }, 
	{ "GetPermRangeBans", GetPermRangeBans }, 
	{ "GetRangeBan", GetRangeBan }, 
	{ "GetRangePermBan", GetRangePermBan }, 
	{ "GetRangeTempBan", GetRangeTempBan }, 
	{ "Unban", Unban }, 
	{ "UnbanPerm", UnbanPerm }, 
	{ "UnbanTemp", UnbanTemp }, 
	{ "UnbanAll", UnbanAll }, 
	{ "UnbanPermAll", UnbanPermAll }, 
	{ "UnbanTempAll", UnbanTempAll }, 
	{ "RangeUnban", RangeUnban }, 
	{ "RangeUnbanPerm", RangeUnbanPerm }, 
	{ "RangeUnbanTemp", RangeUnbanTemp }, 
	{ "ClearBans", ClearBans }, 
	{ "ClearPermBans", ClearPermBans }, 
	{ "ClearTempBans", ClearTempBans }, 
	{ "ClearRangeBans", ClearRangeBans }, 
	{ "ClearRangePermBans", ClearRangePermBans }, 
	{ "ClearRangeTempBans", ClearRangeTempBans }, 
	{ "Ban", Ban }, 
	{ "BanIP", BanIP }, 
	{ "BanNick", BanNick }, 
	{ "TempBan", TempBan }, 
	{ "TempBanIP", TempBanIP }, 
	{ "TempBanNick", TempBanNick }, 
	{ "RangeBan", RangeBan }, 
	{ "RangeTempBan", RangeTempBan }, 
	{ NULL, NULL }
};
//---------------------------------------------------------------------------

void RegBanMan(lua_State * L) {
    luaL_register(L, "BanMan", banman_funcs);
}
//---------------------------------------------------------------------------