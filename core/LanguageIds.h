/*
 * PtokaX - hub server for Direct Connect peer to peer network.

 * Copyright (C) 2002-2005  Ptaczek, Ptaczek at PtokaX dot org
 * Copyright (C) 2004-2011  Petr Kozelka, PPK at PtokaX dot org

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
#ifndef LanguageIdsH
#define LanguageIdsH
//---------------------------------------------------------------------------

enum LangIds {
    LAN_THIS_HUB_IS_RUNNING,
    LAN_HUB_NAME,
    LAN_MOTD,
    LAN_HUB_TOPIC,
    LAN_HUB_DESCRIPTION,
    LAN_ANTI_MOGLO,
    LAN_HUB_ADDRESS,
    LAN_RESOLVE_HOST,
    LAN_BIND_ONLY_ADDR,
    LAN_TCP_PORTS,
    LAN_TCP_PORTS_HINT,
    LAN_UDP_PORT,
    LAN_ADMIN_NICK,
    LAN_REDIRECT_ADDRESS,
    LAN_REDIRECT_ALL_CONN,
    LAN_REDIRECT_FULL,
    LAN_HUB_REG_ADRS,
    LAN_AUTO_REG,
    LAN_HUB_AUTO_START,
    LAN_START_HUB,
    LAN_STOP_HUB,
    LAN_DISABLE_MOTD,
    LAN_MOTD_IN_PM,
    LAN_USERS_CHAT,
    LAN_ADMIN_CHAT,
    LAN_AUTO,
    LAN_REFRESH_USERLIST,
    LAN_CLS,
    LAN_CHAT,
    LAN_CMDS,
    LAN_MASS_MSG,
    LAN_REDIRECT_ALL_USERS,
    LAN_REG_USERS,
    LAN_USER,
    LAN_PASSWORD,
    LAN_PROFILE,
    LAN_NEW,
    LAN_MODIFY,
    LAN_REMOVE,
    LAN_REFRESH_BANS,
    LAN_REFRESH_RANGE_BANS,
    LAN_IP,
    LAN_NICK,
    LAN_BANNED_BY,
    LAN_REASON,
    LAN_EXPIRE,
    LAN_RANGE,
    LAN_TEMP_BANS,
    LAN_CLEAR_BANS,
    LAN_CLEAR_RANGE_BANS,
    LAN_REDIRECT,
    LAN_PERM_BANS,
    LAN_RULES,
    LAN_MIN_SHARE,
    LAN_MAX_SHARE,
    LAN_MIN_SLOTS,
    LAN_MAX_SLOTS,
    LAN_MAX_HUBS,
    LAN_ACCEPT,
    LAN_REJECT,
    LAN_MSG_TO_SND,
    LAN_NICK_LIMITS,
    LAN_MIN_LEN,
    LAN_MAX_LEN,
    LAN_SCRIPTS_MEMORY,
    LAN_SCRIPT_FILE,
    LAN_MEM_USAGE,
    LAN_MOVE_UP,
    LAN_LUA_MOVE_UP_HINT,
    LAN_MOVE_DOWN,
    LAN_LUA_MOVE_DOWN_HINT,
    LAN_CHECK_SYNTAX,
    LAN_CHECK_SYNTAX_HINT,
    LAN_RESTART_SCRIPTS,
    LAN_RESTART_SCRIPTS_HINT,
    LAN_LOAD,
    LAN_LUA_LOAD_HINT,
    LAN_SAVE,
    LAN_LUA_SAVE_HINT,
    LAN_ENABLE_TRAY_ICON,
    LAN_MINIMIZE_ON_STARTUP,
    LAN_ENABLE_SCRIPTING,
    LAN_STOP_SCRIPT_ON_ERR,
    LAN_REPLY_HUB_CMDS_PM,
    LAN_FILTER_KICKS,
    LAN_FILTERED_KICKS_TO_OPS,
    LAN_SEND_STATUS,
    LAN_SEND_STATUS_PM,
    LAN_DISALLOW_PINGERS,
    LAN_REPORT_PINGERS,
    LAN_REPORT_BAD_TAGS,
    LAN_REPORT_BAD_PASS,
    LAN_ADV_PASS_PRTCTN,
    LAN_USE_USERIP,
    LAN_ACCEPT_UNKNOWN_TAG,
    LAN_CHECK_IPS,
    LAN_KEEP_SLOW,
    LAN_UPDATE_CHECK_ON_STARTUP,
    LAN_CHECK_UPDATE_NOW,
    LAN_MYINFO_PROCESSING,
    LAN_FULL_MYINFO_ALL,
    LAN_FULL_MYINFO_PROFILE,
    LAN_FULL_MYINFO_NONE,
    LAN_MODE_TO_MYINFO,
    LAN_MODE_TO_DESCR,
    LAN_DONT_SEND_MYINFO_CHANGES,
    LAN_REG_ONLY_HUB,
    LAN_LANGUAGE,
    LAN_SAVE_SETTINGS,
    LAN_PROFILE_MAN,
    LAN_HUB_BOT,
    LAN_USE_AS_ALIAS,
    LAN_MINUTES_LWR,
    LAN_TEXT_FILES,
    LAN_ENABLE_TEXT_FILES,
    LAN_TEXT_FILES_PM,
    LAN_REFRESH_TEXT_FILES,
    LAN_BAN_MSG,
    LAN_SHOW_BANNED_IP,
    LAN_SHOW_BANNED_RANGE,
    LAN_SHOW_BANNED_NICK,
    LAN_SHOW_BAN_REASON,
    LAN_SHOW_BAN_WHO,
    LAN_BAN_MSG_ADD_MSG,
    LAN_DEFLOOD,
    LAN_MAIN_CHAT,
    LAN_DISABLED,
    LAN_IGNORE,
    LAN_WARN,
    LAN_DISCONNECT,
    LAN_KICK,
    LAN_TEMP_BAN,
    LAN_PERM_BAN,
    LAN_SEC_LWR,
    LAN_SAME_MAIN_CHAT,
    LAN_SAME_MULTI_MAIN_CHAT,
    LAN_WITH_LWR,
    LAN_LINES_LWR,
    LAN_PRIVATE_MSGS,
    LAN_SAME_PRIVATE_MSGS,
    LAN_SAME_MULTI_PRIVATE_MSGS,
    LAN_SEARCH,
    LAN_SAME_SEARCH,
    LAN_MYINFOS,
    LAN_GETNICKLISTS,
    LAN_MIN_LWR,
    LAN_GLOBAL_MAIN_CHAT,
    LAN_LOCK_CHAT,
    LAN_ONLY_TO_OPS_WITH_IP,
    LAN_FOR,
    LAN_WARN_SET,
    LAN_AFTER,
    LAN_WARNINGS,
    LAN_PM_LIMITS,
    LAN_LENGTH,
    LAN_LINES,
    LAN_MAIN_CHAT_LIMITS,
    LAN_SEARCH_LIMITS,
    LAN_REPORT_FLOOD,
    LAN_MAX_USERS_LOGINS,
    LAN_BRUTE_FORCE_PASS_PRTC_ACT,
    LAN_YEARS_LWR, 
    LAN_YEAR_LWR, 
    LAN_MONTHS_LWR, 
    LAN_MONTH_LWR, 
    LAN_DAYS_LWR, 
    LAN_DAY_LWR, 
    LAN_HOURS_LWR, 
    LAN_HOUR_LWR, 
    LAN_SORRY_PERM_BANNED, 
    LAN_SORRY_TEMP_BANNED, 
    LAN_UPTIME, 
    LAN_USER_INFO,
    LAN_UDP_SCK_CREATE_ERR, 
    LAN_UDP_NON_BLOCK_FAIL, 
    LAN_YOU_SUBSCRIBED_UDP_DBG, 
    LAN_TO_UNSUB_UDP_DBG, 
    LAN_YOU_REDIR_TO, 
    LAN_SRY_LST_MSG_BCS, 
    LAN_EXC_MSG_LIMIT, 
    LAN_SORRY_LAST, 
    LAN_MSGS_NOT_SENT, 
    LAN_UNB_CRT_SRVR_SCK, 
    LAN_ERROR_CODE, 
    LAN_SRV_SCKOPT_ERR, 
    LAN_FOR_PORT_LWR, 
    LAN_SRV_BIND_ERR, 
    LAN_SRV_LISTEN_ERR, 
    LAN_ADD, 
    LAN_SET_ALL, 
    LAN_CLEAR_ALL,
    LAN_ENT_FULL_HUB, 
    LAN_ALLOW_LOGIN_BANNED_IP, 
    LAN_DROP, 
    LAN_GET_USER_INFO, 
    LAN_REDIR, 
    LAN_TEMPOR_BAN, 
    LAN_TEMPOR_UNBAN, 
    LAN_PERMANENT_BAN, 
    LAN_UNBAN_PERM_UNBAN, 
    LAN_CLEAR_TEMP_BANS, 
    LAN_CLEAR_PERM_BANS, 
    LAN_GET_BANS, 
    LAN_RANGE_PERM_BAN, 
    LAN_RANGE_UNBAN_RANGE_PERM_UNBAN, 
    LAN_TEMP_RANGE_BAN, 
    LAN_TEMP_RANGE_UNBAN, 
    LAN_GET_RANGE_BANS, 
    LAN_CLEAR_PERM_RANGE_BANS, 
    LAN_CLEAR_TEMP_RANGE_BANS,
    LAN_GAG_UNGAG, 
    LAN_TEMP_OP, 
    LAN_START_STOP_RESTART_SCRIPTS, 
    LAN_RESTART_HUB, 
    LAN_RLD_TXT_FILES, 
    LAN_NO_SHARE_LIMIT, 
    LAN_NO_SLOT_CHECK, 
    LAN_NO_RATIO_CHECK, 
    LAN_NO_MAX_HUBS_CHECK, 
    LAN_NO_CHAT_LIMITS, 
    LAN_NO_TAG_CHECK, 
    LAN_NO_MAIN_DFLD, 
    LAN_NO_PM_DFLD, 
    LAN_NO_SEARCH_LIMITS, 
    LAN_NO_SEARCH_DFLD, 
    LAN_NO_MYINFO_DFLD,
    LAN_NO_GETNICKLIST_DFLD, 
    LAN_TOPIC, 
    LAN_ADD_REG_USER,
    LAN_DEL_REG_USER, 
    LAN_ALLOW_OPCHAT, 
    LAN_SEND_FULL_MYINFOS, 
    LAN_SEND_USER_IPS, 
    LAN_DONT_CHECK_IP, 
    LAN_HAVE_KEY_IS_OP, 
    LAN_PROFILES_LOAD_FAIL, 
    LAN_PROFILE_DEL_FAIL, 
    LAN_FAILED, 
    LAN_NAME, 
    LAN_NEW_PROFILE_NAME, 
    LAN_PROFILE_NAME_EXIST,
    LAN_REGISTERED_USER,
    LAN_NICKNAME,
    LAN_USER_PROFILE,
    LAN_DISCARD, 
    LAN_ERROR,
    LAN_NOTE, 
    LAN_NICK_MUST_SPECIFIED, 
    LAN_PASS_MUST_SPECIFIED, 
    LAN_NO_BAD_CHARS_IN_NICK, 
    LAN_NO_PIPE_IN_PASS, 
    LAN_USER_IS_ALREDY_REG, 
    LAN_USER_WITH_SAME_NICK_ALREDY_REG, 
    LAN_ERROR_IN_SCRIPT, 
    LAN_NO_SYNERR_IN_SCRIPT_FILE, 
    LAN_NO_SYNERR_IN_SCRIPT, 
    LAN_SYNTAX, 
    LAN_YOU_BEING_KICKED_BCS, 
    LAN_WAS_KICKED_BCS, 
    LAN_WAS_KICKED_BY, 
    LAN_BECAUSE_LWR, 
    LAN_MESSAGE, 
    LAN_FLOODING, 
    LAN_FLOODER, 
    LAN_WITH_IP, 
    LAN_DISCONN_BY_SCRIPT, 
    LAN_FATAL_ERR_SCRIPT, 
    LAN_SCRIPT_STOPPED, 
    LAN_BANNED, 
    LAN_BY, 
    LAN_FULL, 
    LAN_NO_BANS_FOUND, 
    LAN_SNTX_ERR_IN_CMD, 
    LAN_NICK_LWR, 
    LAN_NO_PARAM_GIVEN, 
    LAN_IS_NOT_IN_USERLIST, 
    LAN_IS_ALREDY_GAGGED, 
    LAN_NOT_ALW_TO_GAG, 
    LAN_YOU_GAGGED_BY, 
    LAN_HAS_GAGGED, 
    LAN_STATUS, 
    LAN_ONLINE_FROM, 
    LAN_SHARE_SIZE,
    LAN_DESCRIPTION, 
    LAN_TAG, 
    LAN_CONNECTION, 
    LAN_EMAIL, 
    LAN_NO_TEMP_BANS_FOUND, 
    LAN_SCRIPTS, 
    LAN_NO_PERM_BANS_FOUND, 
    LAN_TEMP_RANGE_BANS, 
    LAN_PERM_RANGE_BANS, 
    LAN_NO_RANGE_BANS_FOUND, 
    LAN_NO_RANGE_PERM_BANS_FOUND, 
    LAN_NO_RANGE_TEMP_BANS_FOUND, 
    LAN_REASON_LWR, 
    LAN_NO_NICK_SPECIFIED, 
    LAN_YOU_CANT_BAN_YOURSELF, 
    LAN_YOU_NOT_ALLOWED_TO, 
    LAN_YOU_HAD_BEEN_BANNED_BCS, 
    LAN_NO_REASON_SPECIFIED, 
    LAN_IS_ALREDY_BANNED_DISCONNECT, 
    LAN_IS_ALREDY_BANNED, 
    LAN_ADDED_LWR, 
    LAN_TO_BANS, 
    LAN_HAS_BEEN_BANNED_BY, 
    LAN_ADDED_TO_BANS, 
    LAN_TIME_LWR, 
    LAN_BAD_TIME_SPECIFIED, 
    LAN_YOU_HAD_BEEN_TEMP_BANNED_TO, 
    LAN_ALRD_BND_LNGR_TIME_DISCONNECTED, 
    LAN_IS_ALRD_BANNED_LONGER_TIME, 
    LAN_HAS_BEEN_TMPBND_BY, 
    LAN_TO_LWR, 
    LAN_BEEN_TEMP_BANNED_TO, 
    LAN_SORRY, 
    LAN_IS_NOT_IN_MY_TEMP_BANS, 
    LAN_REMOVED_LWR, 
    LAN_FROM_TEMP_BANS,
    LAN_REMOVED_FROM_TEMP_BANS, 
    LAN_TOPIC_HAS_BEEN_CLEARED, 
    LAN_TOPIC_HAS_BEEN_SET_TO, 
    LAN_NEW_TOPIC, 
    LAN_YOUR_IP_IS, 
    LAN_MESSAGE_LWR, 
    LAN_MASSMSG_TO_ALL_SENT, 
    LAN_ERR_SCRIPTS_DISABLED, 
    LAN_RESTARTED_SCRIPTS, 
    LAN_SCRIPTS_RESTARTED, 
    LAN_HUB_WILL_BE_RESTARTED, 
    LAN_BACK_IN_FEW_MINUTES, 
    LAN_TXT_SUP_NOT_ENABLED, 
    LAN_RELOAD_TXT_FILES_LWR, 
    LAN_TXT_FILES_RELOADED, 
    LAN_SCRIPTNAME_LWR, 
    LAN_ERROR_SCRIPT, 
    LAN_NOT_RUNNING, 
    LAN_RESTARTED_SCRIPT, 
    LAN_SCRIPT, 
    LAN_RESTARTED_LWR, 
    LAN_RESTART_FAILED, 
    LAN_FROMIP, 
    LAN_TOIP, 
    LAN_IP_OR_NICK, 
    LAN_IS_NOT_IN_BANS, 
    LAN_FROM_BANS, 
    LAN_REMOVED_FROM_BANS, 
    LAN_IS_NOT_GAGGED, 
    LAN_YOU_ARE_UNGAGGED_BY, 
    LAN_HAS_UNGAGGED, 
    LAN_ALREDY_IS_OP, 
    LAN_OPERATOR_PROFILE_MISSING, 
    LAN_YOU_GOT_TEMP_OP, 
    LAN_SETS_OP_MODE_TO, 
    LAN_GOT_OP_STATUS, 
    LAN_MASSMSG_TO_OPS_SND,
    LAN_DROP_ADDED_TEMPBAN_BY, 
    LAN_DROP_ADDED_TEMPBAN_BCS, 
    LAN_CMD_TOO_LONG, 
    LAN_IS_NOT_IN_REGS, 
    LAN_YOURE_NOT_ALWD_TO_DLT_USER_THIS_PRFL, 
    LAN_FROM_REGS, 
    LAN_REMOVED_FROM_REGS, 
    LAN_PORT_LWR, 
    LAN_UNSUB_FROM_UDP_DBG, 
    LAN_UNABLE_FIND_UDP_DBG_INTER, 
    LAN_NOT_UDP_DEBUG_SUBSCRIB, 
    LAN_ALRD_UDP_SUBSCRIP_TO_UNSUB, 
    LAN_IN_MAINCHAT, 
    LAN_SUBSCIB_UDP_DEBUG_ON_PORT, 
    LAN_TO_UNSUB_TYPE, 
    LAN_UDP_DEBUG_SUBSCRIB_FAILED, 
    LAN_HAS_CLEARED_TEMPBANS, 
    LAN_TEMP_BANS_CLEARED, 
    LAN_HAS_CLEARED_PERMBANS, 
    LAN_PERM_BANS_CLEARED, 
    LAN_TEMP_RANGE_BANS_CLEARED, 
    LAN_HAS_CLEARED_PERM_RANGEBANS, 
    LAN_PERM_RANGE_BANS_CLEARED, 
    LAN_NO_BAN_FOUND, 
    LAN_BANNED_NICK, 
    LAN_NO_VALID_IP_SPECIFIED, 
    LAN_BANNED_IP, 
    LAN_BAD_PARAMS_GIVEN, 
    LAN_NO_VALID_IP_RANGE_SPECIFIED, 
    LAN_NO_RANGE_BAN_FOUND, 
    LAN_PASSWORD_LWR,
    LAN_PROFILENAME_LWR, 
    LAN_MAX_ALWD_NICK_LEN_64_CHARS, 
    LAN_MAX_ALWD_PASS_LEN_64_CHARS, 
    LAN_ERR_NO_PROFILE_GIVEN_NAME_EXIST, 
    LAN_YOU_NOT_ALLOWED_TO_ADD_USER_THIS_PROFILE,
    LAN_IS_ALREDY_REGISTERED, 
    LAN_SUCCESSFULLY_ADDED, 
    LAN_TO_REGISTERED_USERS, 
    LAN_SUCCESSFULLY_ADDED_TO_REGISTERED_USERS, 
    LAN_FOLOW_COMMANDS_AVAILABLE_TO_YOU, 
    LAN_PROFILE_SPECIFIC_CMDS, 
    LAN_NEW_PASSWORD, 
    LAN_CHANGE_YOUR_PASSWORD, 
    LAN_PERM_BAN_USER_GIVEN_NICK_DISCONNECT, 
    LAN_PERM_BAN_IP_ADDRESS, 
    LAN_BAN_USERS_NICK_IFCONN_THENDISCONN, 
    LAN_TEMP_BAN_USER_GIVEN_NICK_DISCONNECT, 
    LAN_TEMP_BAN_IP_ADDRESS, 
    LAN_TEMP_BAN_USERS_NICK_IFCONN_THENDISCONN, 
    LAN_UNBAN_IP_OR_NICK, 
    LAN_UNBAN_PERM_BANNED_IP_OR_NICK, 
    LAN_UNBAN_TEMP_BANNED_IP_OR_NICK, 
    LAN_DISPLAY_LIST_OF_BANS, 
    LAN_DISPLAY_LIST_OF_PERM_BANS, 
    LAN_DISPLAY_LIST_OF_TEMP_BANS, 
    LAN_CLEAR_PERM_BANS_LWR,
    LAN_CLEAR_TEMP_BANS_LWR,
    LAN_PERM_BAN_GIVEN_IP_RANGE, 
    LAN_TEMP_BAN_GIVEN_IP_RANGE, 
    LAN_UNBAN_BANNED_IP_RANGE, 
    LAN_UNBAN_PERM_BANNED_IP_RANGE, 
    LAN_UNBAN_TEMP_BANNED_IP_RANGE, 
    LAN_DISPLAY_LIST_OF_RANGE_BANS, 
    LAN_DISPLAY_LIST_OF_RANGE_PERM_BANS, 
    LAN_DISPLAY_LIST_OF_RANGE_TEMP_BANS, 
    LAN_CLEAR_PERM_RANGE_BANS_LWR, 
    LAN_CLEAR_TEMP_RANGE_BANS_LWR, 
    LAN_DISPLAY_BAN_FOUND_FOR_GIVEN_NICK, 
    LAN_DISPLAY_BANS_FOUND_FOR_GIVEN_IP, 
    LAN_DISPLAY_RANGE_BAN_FOR_GIVEN_RANGE, 
    LAN_DISCONNECT_WITH_TEMPBAN, 
    LAN_DISPLAY_INFO_GIVEN_NICK,
    LAN_GIVE_TEMP_OP, 
    LAN_DISALLOW_USER_TO_POST_IN_MAIN, 
    LAN_USER_CAN_POST_IN_MAIN_AGAIN, 
    LAN_RESTART_HUB_LWR, 
    LAN_FILENAME_LWR, 
    LAN_START_SCRIPT_GIVEN_FILENAME, 
    LAN_STOP_SCRIPT_GIVEN_FILENAME, 
    LAN_RESTART_SCRIPT_GIVEN_FILENAME, 
    LAN_RESTART_SCRIPTING_PART_OF_THE_HUB, 
    LAN_DISPLAY_LIST_OF_SCRIPTS, 
    LAN_RELOAD_ALL_TEXT_FILES, 
    LAN_ADD_REG_USER_WITH_PROFILE, 
    LAN_REMOVE_REG_USER, 
    LAN_SET_NEW_TOPIC_OR, 
    LAN_CLEAR_TOPIC, 
    LAN_SEND_MSG_TO_ALL_USERS, 
    LAN_SEND_MSG_TO_ALL_OPS, 
    LAN_REASON_IS_ALWAYS_OPTIONAL, 
    LAN_FULLBAN_HELP_TXT, 
    LAN_TEMPBAN_TIME_VALUES, 
    LAN_GLOBAL_COMMANDS, 
    LAN_SPEAK_IN_3RD_PERSON, 
    LAN_SHOW_YOUR_IP, 
    LAN_STOPPED_SCRIPT, 
    LAN_STOPPED_LWR, 
    LAN_ERROR_SCRIPT_ALREDY_RUNNING, 
    LAN_ERROR_SCRIPT_NOT_EXIST, 
    LAN_STARTED_SCRIPT, 
    LAN_STARTED_LWR, 
    LAN_START_FAILED, 
    LAN_YOU_ARE_NOT_ALLOWED_TO_CHANGE_PASS, 
    LAN_YOUR_PASSWORD_UPDATE_SUCCESS, 
    LAN_IS_NOT_ONLINE, 
    LAN_YOU_ARE_NOT_ALWD_TO_BAN, 
    LAN_HAS_BEEN,
    LAN_BY_LWR, 
    LAN_IS_LWR, 
    LAN_IS_ALREADY, 
    LAN_YOU_ARE_NOT_ALWD_TO_TEMPBAN, 
    LAN_TO_LONGER_TIME, 
    LAN_ERROR_FROM, 
    LAN_IS_NOT_VALID_RANGE, 
    LAN_BAN_LWR, 
    LAN_TEMP_BAN_NICK, 
    LAN_DROP_LWR, 
    LAN_BANNED_LWR, 
    LAN_TEMP_BANNED, 
    LAN_IS_NOT_IN_MY_RANGE, 
    LAN_TEMP_BANS_LWR,
    LAN_PERM_BANS_LWR,
    LAN_IS_REMOVED_FROM_RANGE, 
    LAN_IS_NOT_IN_MY_RANGE_BANS, 
    LAN_IS_REMOVED_FROM_RANGE_BANS_BY, 
    LAN_IS_REMOVED_FROM_RANGE_BANS, 
    LAN_YOU_ARE_NOT_ALWD_TO_USE_THIS_CMD,
    LAN_WEEKS_LWR, 
    LAN_HAVE_NOT_EXIST_PROFILE, 
    LAN_CHANGED_PROFILE_TO, 
    LAN_IS_ALREADY_IN_REGS, 
    LAN_USER_DELETED, 
    LAN_READY, 
    LAN_SELECT_USER, 
    LAN_YOU_ARE_BEING_KICKED, 
    LAN_IS_KICKING, 
    LAN_MEM, 
    LAN_USERS, 
    LAN_CLIENT, 
    LAN_VERSION,
    LAN_MODE, 
    LAN_SLOTS, 
    LAN_HUBS,
    LAN_AUTO_OPEN_SLOT_WHEN_UP_UNDER, 
    LAN_ARE_YOU_SURE, 
    LAN_BAN, 
    LAN_YOU_ARE_BEING_BANNED, 
    LAN_YOU_ARE_BEING_BANNED_BECAUSE, 
    LAN_RESOLVING_HUB_ADDRESS, 
    LAN_RESOLVING_OF_HOSTNAME, 
    LAN_HAS_FAILED, 
    LAN_CHECK_THE_ADDRESS_PLEASE, 
    LAN_RESOLVED_SUCCESSFULLY, 
    LAN_RUNNING, 
    LAN_STOPPED, 
    LAN_FILE, 
    LAN_NOT_EXIST, 
    LAN_LOADED, 
    LAN_SAVING_FAILED, 
    LAN_UPDATE_CHECK_FAILED, 
    LAN_NEW_VERSION, 
    LAN_RELEASED_ON, 
    LAN_CHANGES, 
    LAN_OPEN_PtokaX_HOMEPAGE, 
    LAN_SORRY_NO_NEW_VERSION_AVAILABLE, 
    LAN_READY_LWR, 
    LAN_TOTAL, 
    LAN_LOGGED, 
    LAN_CLOSING, 
    LAN_LOGGING, 
    LAN_SCRIPT_STARTED, 
    LAN_WARNING, 
    LAN_SCRIPT_WAS_NOT_INITIALIZED, 
    LAN_LOAD_SCRIPT, 
    LAN_SAVE_SCRIPT,
    LAN_SAVED_LWR, 
    LAN_FULL_BANNED, 
    LAN_NICK_BAN, 
    LAN_IP_BAN, 
    LAN_PERMANENT, 
    LAN_GLOBAL_CHAT_FLOOD_DETECTED, 
    LAN_YOU_MyINFO_IS_CORRUPTED, 
    LAN_FAKE_TAG, 
    LAN_HAS_SUSPICIOUS_TAG_CHECK_HIM, 
    LAN_FULL_DESCRIPTION, 
    LAN_PINGER_FROM_IP, 
    LAN_WITH_NICK, 
    LAN_DETECTED_LWR, 
    LAN_PLS_DONT_FLOOD_WITH_GetNickList, 
    LAN_YOU_ARE_BEING_DISCONNECTED_BECAUSE, 
    LAN_GetNickList_FLOODING, 
    LAN_GetNickList_FLOODER, 
    LAN_DISCONNECTED_LWR, 
    LAN_WAS_KICKED, 
    LAN_WAS_TEMPORARY_BANNED, 
    LAN_WAS_BANNED, 
    LAN_YOU_CANT_KICK_YOURSELF, 
    LAN_YOU_ARE_NOT_ALLOWED_TO_KICK, 
    LAN_PLS_DONT_FLOOD_WITH_SEARCHES, 
    LAN_SEARCH_FLOODING, 
    LAN_SEARCH_FLOODER, 
    LAN_SORRY_MIN_SEARCH_LEN_IS, 
    LAN_SORRY_MAX_SEARCH_LEN_IS, 
    LAN_PLS_DONT_FLOOD_WITH_MyINFO, 
    LAN_MyINFO_FLOODING, 
    LAN_MyINFO_FLOODER, 
    LAN_YOUR_IP_BANNED_BRUTE_FORCE_ATTACK, 
    LAN_YOUR_IS_BANNED, 
    LAN_BANNED_BECAUSE_3X_BAD_PASS_FOR_NICK, 
    LAN_INCORRECT_PASSWORD,
    LAN_YOU_ARE_NOT_ALLOWED_TO_REDIRECT, 
    LAN_YOU_ARE_REDIRECTED_TO, 
    LAN_IS_REDIRECTED_TO, 
    LAN_SORRY_THIS_HUB_NOT_ALLOW_PINGERS, 
    LAN_PLS_DONT_FLOOD_WITH_PM, 
    LAN_PM_FLOODING, 
    LAN_PM_FLOODER, 
    LAN_THE_MESSAGE_WAS_TOO_LONG, 
    LAN_PLS_DONT_FLOOD_CHAT, 
    LAN_CHAT_FLOODING, 
    LAN_CHAT_FLOODER, 
    LAN_YOUR_NICK_CONTAINS_ILLEGAL_CHARACTER, 
    LAN_PLS_CORRECT_IT_AND_GET_BACK_AGAIN, 
    LAN_THE_NICK_IS_RESERVED_FOR_SOMEONE_OTHER, 
    LAN_CHANGE_YOUR_NICK_AND_GET_BACK_AGAIN, 
    LAN_LAST_PASS_WAS_WRONG_YOU_NEED_WAIT, 
    LAN_BEFORE_YOU_TRY_AGAIN, 
    LAN_THIS_HUB_IS_FULL, 
    LAN_USERS_ONLINE_LWR, 
    LAN_KICK_USER, 
    LAN_BAN_USER, 
    LAN_OP_USER, 
    LAN_YOU_CANT_DROP_YOURSELF, 
    LAN_YOU_CANT_GAG_YOURSELF, 
    LAN_CLOSE, 
    LAN_YOU_CANT_CLOSE_YOURSELF, 
    LAN_YOU_ARE_NOT_ALLOWED_TO_CLOSE, 
    LAN_WAS_CLOSED_BY, 
    LAN_WAS_CLOSED, 
    LAN_FULL_LWR, 
    LAN_DESCRIPTION_TAG, 
    LAN_NO_TAG_ACTION, 
    LAN_MAX_USERS_LIMIT, 
    LAN_TEMP_BAN_TIME_AFTER_ETC, 
    LAN_HUB_OWNER_EMAIL, 
    LAN_MAIN_REDIR_ADDRESS, 
    LAN_REG_ONLY_MSG, 
    LAN_PSR_LIMIT, 
    LAN_OP_CHAT_BOT, 
    LAN_TEMP_BAN_REDIR_ADDRESS, 
    LAN_PERM_BAN_REDIR_ADDRESS, 
    LAN_NEW_CONNS_FRM_SINGLE_IP_LIM, 
    LAN_PM_LIM_TO_URS_FRM_MULTI_NICKS, 
    LAN_DEFLOOD_TEMP_BAN_TIME, 
    LAN_MAX_HUBS_LIMIT, 
    LAN_SLOTS_LIMIT, 
    LAN_HUB_SLOT_RATIO_LIMIT, 
    LAN_SHARE_LIMITS, 
    LAN_EXPERTS_ONLY, 
    LAN_PASSWORD_PROTECTION, 
    LAN_HUB_STARTUP_AND_TRAY_ICON, 
    LAN_HUB_COMMANDS, 
    LAN_SCRIPTING, 
    LAN_KICK_MESSAGES, 
    LAN_STATUS_MESSAGES, 
    LAN_PINGER, 
    LAN_ALLOW_ONLY_REGS, 
    LAN_ENABLE_W_ARROW, 
    LAN_ENABLE_AND_REG_BOT_ON_HUB, 
    LAN_SECONDS_LWR, 
    LAN_MINIMUM, 
    LAN_MAXIMUM, 
    LAN_MAX_MSGS_TO_ONE_USER_PER_MIN, 
    LAN_PER_10_SECONDS, 
    LAN_TEMPORARY_BAN_TIME, 
    LAN_PREFIXES_FOR_HUB_CMDS, 
    LAN_GENERAL_SETTINGS, 
    LAN_MOTD_ONLY, 
    LAN_DEFAULT_BOTS, 
    LAN_MORE_GENERAL, 
    LAN_BAN_HANDLING, 
    LAN_ADVANCED, 
    LAN_ADVANCED_SECURITY, 
    LAN_MORE_RULES, 
    LAN_MORE_DEFLOOD, 
    LAN_SETTINGS, 
    LAN_HUB_LIST_REGS_HINT, 
    LAN_MYINFO_TO_HINT, 
    LAN_SHARE_LIMIT_MSG_HINT, 
    LAN_NICK_LIMIT_MSG_HINT, 
    LAN_HUB_SLOT_RATIO_MSG_HINT, 
    LAN_SLOT_LIMIT_MSG_HINT, 
    LAN_HUB_LIMIT_MSG_HINT, 
    LAN_REDIRECT_HINT, 
    LAN_ZERO_IS_UNLIMITED_HINT, 
    LAN_SCRIPTS_MEMORY_USAGE, 
    LAN_BANS, 
    LAN_RANGE_BANS, 
    LAN_ARE_YOU_SURE_WITH_DDOS, 
    LAN_SETTINGS_SAVED, 
    LAN_OPEN_EXT_EDIT, 
    LAN_DELETE_SCRIPT, 
    LAN_REFRESH_SCRIPTS, 
    LAN_POPUP_SCRIPT_WINDOW, 
    LAN_UPDATE_CHECK, 
    LAN_ACCEPTED_CONNECTIONS, 
    LAN_CLOSED_CONNECTIONS, 
    LAN_ACTIVE_CONNECTIONS, 
    LAN_USERS_ONLINE, 
    LAN_RECEIVED, 
    LAN_SENT, 
    LAN_USERS_PEAK, 
    LAN_CHARS_NOT_ALLOWED_IN_PROFILE, 
    LAN_FULL_BAN, 
    LAN_CREATED_BY, 
    LAN_TEMPORARY, 
    LAN_DAY, 
    LAN_MONTH, 
    LAN_YEAR, 
    LAN_HOUR, 
    LAN_MINUTE, 
    LAN_TEMP_BAN_EXPIRATION, 
    LAN_JAN, 
    LAN_FEB, 
    LAN_MAR, 
    LAN_APR, 
    LAN_MAY, 
    LAN_JUN, 
    LAN_JUL, 
    LAN_AUG, 
    LAN_SEP, 
    LAN_OCT, 
    LAN_NOV, 
    LAN_DEC, 
    LAN_FULL_BAN_HINT, 
    LAN_FOR_NICK_BAN_SPECIFY_NICK, 
    LAN_FOR_IP_BAN_SPECIFY_IP,
    LAN_IS_NOT_VALID_IP_ADDRESS, 
    LAN_BAD_TIME_SPECIFIED_BAN_EXPIRED, 
    LAN_SIMILAR_BAN_EXIST, 
    LAN_YOU_CANT_CREATE_BAN_WITHOUT_NICK_OR_IP, 
    LAN_FROM_IP, 
    LAN_TO_IP, 
    LAN_RANGE_BAN, 
    LAN_BAN_NOT_FOUND, 
    LAN_NO_VALID_TCP_PORT_SPECIFIED, 
    LAN_WAS_DISCONNECTED, 
    LAN_PLS_DONT_FLOOD_WITH_SAME_SEARCHES, 
    LAN_SAME_SEARCH_FLOODING, 
    LAN_SAME_SEARCH_FLOODER, 
    LAN_PLS_DONT_FLOOD_WITH_SAME_PM, 
    LAN_SAME_PM_FLOODING, 
    LAN_SAME_PM_FLOODER, 
    LAN_PLS_DONT_FLOOD_SAME_CHAT, 
    LAN_SAME_CHAT_FLOODING, 
    LAN_SAME_CHAT_FLOODER, 
    LAN_PLS_DONT_FLOOD_WITH_SAME_MULTI_PM, 
    LAN_SAME_MULTI_PM_FLOODING, 
    LAN_SAME_MULTI_PM_FLOODER, 
    LAN_PLS_DONT_FLOOD_SAME_MULTI_CHAT, 
    LAN_SAME_MULTI_CHAT_FLOODING, 
    LAN_SAME_MULTI_CHAT_FLOODER, 
    LAN_MORE_MORE_DEFLOOD, 
    LAN_MYINFO_LIMIT, 
    LAN_YOUR_CLIENT_SEND_INCORRECT_IP, 
    LAN_IN_CTM_REQ_REAL_IP_IS, 
    LAN_IN_SEARCH_REQ_REAL_IP_IS, 
    LAN_CONNECTTOME, 
    LAN_NO_CTM_DFLD, 
    LAN_PLS_DONT_FLOOD_WITH_CTM, 
    LAN_CTM_FLOODING, 
    LAN_CTM_FLOODER, 
    LAN_REVCONNECTTOME, 
    LAN_NO_RCTM_DFLD, 
    LAN_PLS_DONT_FLOOD_WITH_RCTM, 
    LAN_RCTM_FLOODING, 
    LAN_RCTM_FLOODER, 
    LAN_CTM_LIMIT, 
    LAN_RCTM_LIMIT, 
    LAN_MYINFO_TOO_LONG, 
    LAN_CTM_TOO_LONG, 
    LAN_RCTM_TOO_LONG, 
    LAN_SR, 
    LAN_NO_SR_DFLD, 
    LAN_PLS_DONT_FLOOD_WITH_SR, 
    LAN_SR_FLOODING, 
    LAN_SR_FLOODER, 
    LAN_SR_LIMIT, 
    LAN_SR_TOO_LONG, 
    LAN_RECV_DATA_FROM_USER, 
    LAN_NO_RECV_DFLD, 
    LAN_PLS_DONT_FLOOD_WITH_DATA, 
    LAN_DATA_FLOODING, 
    LAN_DATA_FLOODER, 
    LAN_INTERVAL, 
    LAN_NO_CHAT_INTERVAL, 
    LAN_NO_PM_INTERVAL, 
    LAN_NO_SEARCH_INTERVAL, 
    LAN_PLEASE_WAIT, 
    LAN_SECONDS_BEFORE_NEXT_CHAT_MSG, 
    LAN_SECONDS_BEFORE_NEXT_PM, 
    LAN_SECONDS_BEFORE_NEXT_SEARCH, 
    LAN_MAX_USR_SAME_IP, 
    LAN_NO_MAX_USR_SAME_IP, 
    LAN_SORRY_ALREADY_MAX_IP_CONNS, 
    LAN_NO_RECONN_TIME, 
    LAN_RECONN_TIME, 
    LAN_MIN, 
    LAN_SECONDS_BEFORE_RECONN, 
    LAN_RENAME, 
    LAN_COUNTRY, 
    LAN_LOG_SCRIPT_ERRORS, 
    LAN_QUACK_SUPPORTS, 
    LAN_CLIENTS_BUGGY_SUPPORTS, 
    LAN_DISALLOW_BUGGY_SUPPORTS, 
    LAN_MAX_ALWD_TOPIC_LEN_256_CHARS,
    LAN_MAX_ALWD_SCRIPT_NAME_LEN_256_CHARS,
    LAN_MAX_ALWD_IP_LEN_15_CHARS,
    LAN_VIEW,
    LAN_HELP,
    LAN_EXIT,
    LAN_WEBSITE,
    LAN_BOARD,
    LAN_WIKI,
    LAN_MENU_ABOUT,
    LAN_CHECK_FOR_UPDATE,
    LAN_RELOAD_TEXT_FILES,
    LAN_REDIRECT_ALL_USERS_TO,
    LAN_SEND_ORIGINAL_MYINFO,
    LAN_OPTIONS_FOR_MODIFIED_MYINFO,
    LAN_REMOVE_DESCRIPTION,
    LAN_REMOVE_TAG,
    LAN_REMOVE_CONNECTION,
    LAN_REMOVE_EMAIL,
    LAN_ZERO_DISABLED,
    LAN_LWR_KILO_BYTES,
    LAN_BYTES,
    LAN_KILO_BYTES,
    LAN_MEGA_BYTES,
    LAN_GIGA_BYTES,
    LAN_TERA_BYTES,
    LAN_MENU_SETTINGS,
    LAN_ABOUT,
    LAN_STATS,
    LAN_MENU_COPY,
    LAN_MENU_SELECT_ALL,
    LAN_MENU_REG_USER,
    LAN_MENU_DISCONNECT_USER,
    LAN_MENU_KICK_USER,
    LAN_MENU_BAN_USER,
    LAN_MENU_REDIRECT_USER,
    LAN_PLEASE_ENTER_REASON,
    LAN_WAS_REDIRECTED_TO,
    LAN_PLEASE_ENTER_REDIRECT_ADDRESS,
    LAN_LIMITER,
    LAN_SCRIPTS_ERRORS,
    LAN_SCRIPT_EDITOR,
    LAN_OPEN_SCRIPT_EDITOR,
    LAN_FAILED_TO_OPEN,
    LAN_OPEN_IN_SCRIPT_EDITOR,
    LAN_FAILED_TO_SAVE,
    LAN_FAILED_TO_CHECK_SYNTAX,
    LAN_CHANGE,
    LAN_FILTER_REGISTERED_USERS,
    LAN_USER_DELETED_ACCEPT_TO_NEW,
    LAN_USER_CHANGED,
    LAN_ADD_NEW_REG,
    LAN_PROFILES,
    LAN_ADD_NEW_PROFILE,
    LAN_PROFILE_PERMISSIONS,
    LAN_ADD_NEW_BAN,
    LAN_FILTER_BANS,
    LAN_BAN_DELETED_ACCEPT_TO_NEW,
    LAN_ADD_NEW_RANGE_BAN,
    LAN_FILTER_RANGE_BANS,
    LAN_RANGE_BAN_DELETED_ACCEPT_TO_NEW,
    LANG_IDS_END
};
//---------------------------------------------------------------------------

#endif
