/*
 * PtokaX - hub server for Direct Connect peer to peer network.

 * Copyright (C) 2002-2005  Ptaczek, Ptaczek at PtokaX dot org
 * Copyright (C) 2004-2008  Petr Kozelka, PPK at PtokaX dot org

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
#ifndef ProfileManagerH
#define ProfileManagerH
//---------------------------------------------------------------------------
struct User;
//---------------------------------------------------------------------------

struct ProfileItem {
    ProfileItem() { };
    ~ProfileItem();

    char *sName;
    bool bPermissions[256];
};
//---------------------------------------------------------------------------

class ProfileManager {
private:	// User declarations  
    void CreateDefaultProfiles();
    ProfileItem * CreateProfile(const char * name);
public:		// User declarations
    enum ProfilePermissions {
        HASKEYICON,
        NODEFLOODGETNICKLIST,
        NODEFLOODMYINFO,
        NODEFLOODSEARCH,
        NODEFLOODPM,
        NODEFLOODMAINCHAT,
        MASSMSG,
        TOPIC,
        TEMP_BAN,
        REFRESHTXT,
        NOTAGCHECK,
        TEMP_UNBAN,
        DELREGUSER,
        ADDREGUSER,
        NOCHATLIMITS,
        NOMAXHUBCHECK,
        NOSLOTHUBRATIO,
        NOSLOTCHECK,
        NOSHARELIMIT,
        CLRPERMBAN,
        CLRTEMPBAN,
        GETINFO,
        GETBANLIST,
        RSTSCRIPTS,
        RSTHUB,
        TEMPOP,
        GAG,
        REDIRECT,
        BAN,
        KICK,
        DROP,
        ENTERFULLHUB,
        ENTERIFIPBAN,
        ALLOWEDOPCHAT,
        SENDALLUSERIP,
        RANGE_BAN,
        RANGE_UNBAN,
        RANGE_TBAN,
        RANGE_TUNBAN,
        GET_RANGE_BANS,
        CLR_RANGE_BANS,
        CLR_RANGE_TBANS,
        UNBAN,
        NOSEARCHLIMITS, 
        SENDFULLMYINFOS, 
        NOIPCHECK, 
        CLOSE, 
        NODEFLOODCTM, 
        NODEFLOODRCTM, 
        NODEFLOODSR, 
        NODEFLOODRECV, 
        NOCHATINTERVAL, 
        NOPMINTERVAL, 
        NOSEARCHINTERVAL, 
        NOUSRSAMEIP, 
        NORECONNTIME, 
    };

    unsigned int iProfileCount;
    ProfileItem **ProfilesTable;

    ProfileManager();
    ~ProfileManager();

    bool IsAllowed(User * u, const unsigned int &iOption);
    bool IsProfileAllowed(const int &iProfile, const unsigned int &iOption);
    int AddProfile(char * name);
    int GetProfileIndex(const char * name);
    int RemoveProfileByName(char * name);
    void MoveProfileDown(const unsigned int &iProfile);
    void MoveProfileUp(const unsigned int &iProfile);
    void ChangeProfileName(const unsigned int &iProfile, char * sName, const size_t &iLen);
    void ChangeProfilePermission(const unsigned int &iProfile, const size_t &iId, const bool &bValue);
    void SaveProfiles();
};

//---------------------------------------------------------------------------
extern ProfileManager *ProfileMan;
//---------------------------------------------------------------------------

#endif
