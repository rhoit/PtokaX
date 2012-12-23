/*
 * PtokaX - hub server for Direct Connect peer to peer network.

 * Copyright (C) 2002-2005  Ptaczek, Ptaczek at PtokaX dot org
 * Copyright (C) 2004-2012  Petr Kozelka, PPK at PtokaX dot org

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
#ifndef LanguageStringsH
#define LanguageStringsH
//---------------------------------------------------------------------------

const char* LangStr[] = {
    "This hub is running",
    "Hub name",
    "MOTD (message of the day)",
    "Hub topic",
    "Hub description",
    "Anti MoGLO description",
    "Hub address (hostname or IP address)",
    "Resolve hostname to IP addresses",
    "Accept connections only on this addresses",
    "TCP ports",
    "More ports like 4861;666;411",
    "UDP port",
    "Admin nick (used in chat from hub window)",
    "Redirect address",
    "Redirect all connecting users",
    "Redirect users when hub is full",
    "Hublist register addresses",
    "Automatically register to hublist",
    "Automatically start hub server on startup",
    "Start hub",
    "Stop hub",
    "Disable MOTD",
    "Send MOTD as private message",
    "Users / Chat",
    "Auto",
    "Refresh userlist",
    "Chat",
    "CMDs",
    "Mass message",
    "Redirect all users",
    "Registered users",
    "User",
    "Password",
    "Profile",
    "Remove",
    "IP",
    "Nick",
    "Banned by",
    "Reason",
    "Expire",
    "Range",
    "Temporary bans",
    "Permanent bans",
    "Rules",
    "Minimal share",
    "Maximal share",
    "Minimal slots",
    "Maximal slots",
    "Max hubs",
    "Accept",
    "Reject",
    "Message to send",
    "Nick limits",
    "Minimal length",
    "Maximal length",
    "Script file",
    "Memory usage",
    "Move up",
    "Move down",
    "Check syntax",
    "Restart scripts",
    "Enable tray icon and minimize to tray",
    "Minimize to tray on startup (tray icon must be enabled)",
    "Enable Lua scripting inteface",
    "Stop script when Lua find error in it",
    "Reply to hub commands as private message",
    "Filter kick messages (don't send them to all users)",
    "Send kick messages to Operators (when previous option is enabled)",
    "Send status messages to Operators",
    "Send status messages as private messages",
    "Don't allow hublist pingers to check hub",
    "Report hublist pingers to Operators",
    "Report suspicious description tag to operators",
    "Report to Operators when bad password is received 3 times",
    "Enable advanced password protection",
    "Keep slow users online",
    "Check on startup if new PtokaX version is available",
    "MyINFO processing",
    "To all users",
    "Only to allowed profiles",
    "Don't send",
    "Add user connection mode to MyINFO (need support in client)",
    "Add user connection mode to user description",
    "Don't send MyINFO changes (minutes from last send)",
    "Registered users only hub",
    "Language",
    "S&ave settings",
    "Hub bot",
    "Use this nick instead of Hub-Security",
    "minutes",
    "Text files",
    "Enable text files support",
    "Send text files as private message",
    "Ban message",
    "Show banned IP",
    "Show banned range",
    "Show banned nick",
    "Show reason",
    "Show who created ban",
    "Additional message",
    "Deflood",
    "Main chat",
    "Disabled",
    "Ignore",
    "Warn",
    "Disconnect",
    "Kick",
    "Temp Ban",
    "Perm Ban",
    "sec",
    "Same main chat messages",
    "Same main chat with multiline messages",
    "with",
    "lines",
    "Private messages",
    "Same private messages",
    "Same multiline private messages",
    "Search",
    "Same searches",
    "MyINFOs",
    "GetNickLists",
    "min",
    "Global main chat deflood",
    "Lock chat",
    "Send only to OPs with user IP",
    "for",
    "Warn settings",
    "after",
    "warnings",
    "Private message limits",
    "Length",
    "Lines",
    "Main chat limits",
    "Search length limits",
    "Report flood to operators",
    "Max users logins",
    "Brute force password protection action",
    "years", 
    "year", 
    "months", 
    "month", 
    "days", 
    "day", 
    "hours", 
    "hour", 
    "Sorry you are permanently banned", 
    "Sorry you have temp ban with remaining time", 
    "UpTime",
    "UDP Socket creation error",
    "Setting non-blocking mode for UDP socket has failed with ErrCode", 
    "You are subscribed for Debug messaging on port", 
    "To unsubscribe type !debug off in mainchat", 
    "You are being redirected to", 
    "Sorry last message not sent, because", 
    "already exceed messages limit per minute", 
    "Sorry last", 
    "messages not sent, because", 
    "Unable to create server socket for port", 
    "Error Code", 
    "Server socket setsockopt error", 
    "for port", 
    "Server socket bind error", 
    "Server socket listen error", 
    "Set all",
    "Clear all",
    "Enter full hub", 
    "Allowed to login from banned IP (without fullban)", 
    "Drop", 
    "Get user info", 
    "Redirect", 
    "Temporary ban", 
    "Temporary unban", 
    "Permanent Ban", 
    "Unban, Permanent Unban", 
    "Clear temporary bans", 
    "Clear permanent bans", 
    "Get bans", 
    "Range permanent ban", 
    "Range unban, Range permanent unban", 
    "Temporary range ban", 
    "Temporary range unban", 
    "Get range bans", 
    "Clear permanent range bans",
    "Clear temporary range bans",
    "Gag, Ungag", 
    "Temp OP", 
    "Start/Stop/Restart script(s)", 
    "Restart hub", 
    "Reload text files", 
    "No share limit", 
    "No slot check", 
    "No slot/hub check", 
    "No max hubs check", 
    "No chat limits", 
    "No tag check", 
    "No main chat deflood", 
    "No private message deflood", 
    "No search limits", 
    "No search deflood", 
    "No MyINFO deflood", 
    "No GetNickList deflood", 
    "Topic", 
    "Add registered user", 
    "Del registered user", 
    "Allowed for OpChat", 
    "Send long myinfos",
    "Send all users IP", 
    "Don't check IP in DC commands", 
    "Have key / is Op", 
    "Loading of Profiles.xml failed!", 
    "Failed to delete a profile. Profile is in use.", 
    "New profile name",
    "Profile name already exists in the list!",
    "Registered user",
    "Discard",
    "Error",
    "Nick must be specified!",
    "Password must be specified!", 
    "No $<>:?*\"/\\ pipe and <space> in nickname!", 
    "No pipe in Password!", 
    "User is already registered!", 
    "No syntax errors in script file",
    "No syntax errors in the script.", 
    "Syntax", 
    "You are being kicked because", 
    "was kicked by",
    "because", 
    "Message", 
    "Flooding", 
    "Flooder", 
    "with IP", 
    "disconnected by script", 
    "Fatal error in script", 
    "Script stopped", 
    "Banned", 
    "By", 
    "Full", 
    "No bans found", 
    "Syntax error in command", 
    "nick", 
    "No parameter given", 
    "is not in my userlist", 
    "is already gagged", 
    "You are not allowed to gag", 
    "You are gagged by", 
    "has gagged", 
    "Status", 
    "Online from", 
    "Share size",
    "Description", 
    "Tag", 
    "Connection", 
    "Email", 
    "No temporary bans found", 
    "Scripts", 
    "No permanent bans found", 
    "Temporary range bans", 
    "Permanent range bans", 
    "No range bans found", 
    "No permanent range bans found", 
    "No temporary range bans found", 
    "reason", 
    "No nick specified", 
    "You can't ban yourself", 
    "You are not allowed to", 
    "You had been banned because", 
    "No reason specified", 
    "is already banned, user disconnected", 
    "is already banned", 
    "added", 
    "to bans", 
    "has been banned by", 
    "added to bans", 
    "time", 
    "Bad time specified", 
    "You had been temp banned to", 
    "is already banned to longer time, user disconnected", 
    "is already banned to longer time", 
    "has been temp banned by", 
    "to", 
    "has been temp banned to", 
    "Sorry", 
    "is not in my temp bans", 
    "removed", 
    "from temp bans",
    "removed from temp bans", 
    "Topic has been cleared", 
    "Topic has been set to", 
    "new topic", 
    "Your IP is", 
    "message", 
    "Mass message to all sent", 
    "Error, scripting disabled", 
    "restarted scripts", 
    "Scripts restarted", 
    "Hub will be restarted", 
    "Back in a few minutes", 
    "Text files support is not enabled", 
    "reload text files", 
    "Text files reloaded", 
    "scriptname", 
    "Error, script", 
    "not running", 
    "restarted script", 
    "Script", 
    "restarted", 
    "restart failed", 
    "fromIP", 
    "toIP", 
    "IP or nick", 
    "is not in my perm bans", 
    "from bans", 
    "removed from bans", 
    "is not gagged", 
    "You are ungagged by", 
    "has ungagged", 
    "already got the operator status", 
    "Operator profile doesn't exist", 
    "You've got temporal Operator status", 
    "sets Operator mode to", 
    "got the operator status", 
    "Mass message to OPs sent",
    "dropped and added to tempban by", 
    "dropped and added to tempban because", 
    "Command too long", 
    "is not in my registered users", 
    "You are not allowed to delete user with this profile", 
    "from registered users", 
    "removed from registered users", 
    "port", 
    "You have been unsubscribed from Debug messaging", 
    "Im unable to find your Debug messaging interface", 
    "You are not subscriber of Debug messaging service", 
    "You are already subscribed for Debug messaging. To unsubscribe type", 
    "in mainchat", 
    "You are now subscribed for Debug messaging on UDP port", 
    "To unsubscribe type", 
    "Your Debug messaging subscription has failed", 
    "has cleared temp bans", 
    "Temp bans cleared", 
    "has cleared perm bans", 
    "Perm bans cleared", 
    "has cleared temp range bans",
    "Temp range bans cleared", 
    "has cleared perm range bans", 
    "Perm range bans cleared", 
    "No ban found", 
    "Banned nick", 
    "No valid IP specified", 
    "Banned IP", 
    "Bad parameters given", 
    "No valid IP range specified", 
    "No range ban found", 
    "password", 
    "profilename", 
    "Max allowed nick length is 64 characters", 
    "Max allowed password length is 64 characters", 
    "Error, no profile of given name doesn't exist", 
    "You are not allowed add new user with this profile",
    "is already registered", 
    "successfully added", 
    "to registered users", 
    "successfully added to registered users", 
    "The following commands are available to you", 
    "Profile specific commands", 
    "new password", 
    "change your password", 
    "permanently ban user with given nick, followed by disconnect",
    "permanently ban IP address", 
    "ban user's nick (if user is connected then is disconnected)", 
    "temporary ban user with given nick, followed by disconnect", 
    "temporary ban IP address", 
    "temp ban user's nick (if user is connected then is disconnected)", 
    "unban IP address or nick", 
    "unban perm banned IP address or nick", 
    "unban temp banned IP address or nick", 
    "display list of bans", 
    "display list of permanent bans", 
    "display list of temporary bans", 
    "clear perm bans", 
    "clear temp bans", 
    "permanently ban given IP range", 
    "temporary ban given IP range", 
    "unban banned IP range", 
    "unban permanently banned IP range", 
    "unban temporary banned IP range", 
    "display list of range bans", 
    "display list of permanent range bans", 
    "display list of temporary range bans", 
    "clear permanent range bans", 
    "clear temporary range bans", 
    "display ban found for given nick", 
    "display ban(s) found for given IP address", 
    "display range ban found for given IP range", 
    "disconnect with tempban", 
    "displays basic info on user with given nick",
    "give a temporal Op status to the user for one session", 
    "disallow user to post in mainchat", 
    "user can post to mainchat again", 
    "restart hub", 
    "filename", 
    "start script with given filename", 
    "stop script with given filename", 
    "restart script with given filename", 
    "restart scripting part of the hub", 
    "display list of scripts", 
    "reload all textfiles", 
    "add registered user with specified profile", 
    "remove registered user", 
    "Set new topic. Or", 
    "clear topic", 
    "send private message to all users", 
    "send private message to all OPs", 
    "Reason is always optional", 
    "Full bans disallow anyone from banned IP to login", 
    "Temp ban time values", 
    "Global commands", 
    "speak in 3rd person", 
    "show your IP", 
    "stopped script", 
    "stopped", 
    "Error, script already running", 
    "Error, script not exist", 
    "started script", 
    "started", 
    "start failed", 
    "You are not allowed to change your password", 
    "Your password updated successfully", 
    "is not online", 
    "You are not allowed to ban", 
    "has been",
    "by", 
    "is", 
    "is already", 
    "You are not allowed to tempban", 
    "to longer time", 
    "Error, from", 
    "is not a valid range", 
    "ban", 
    "tempban nick", 
    "drop", 
    "banned", 
    "temp banned", 
    "is not in my range", 
    "temp bans", 
    "perm bans", 
    "is removed from range", 
    "is not in my range bans", 
    "is removed from range bans by", 
    "is removed from range bans", 
    "You are not allowed to use this command",
    "weeks",  
    "have none existant profile", 
    "Changed profile to", 
    "is already in regs", 
    "User deleted", 
    "Ready", 
    "You are being kicked",
    "Users",
    "Client", 
    "Version",
    "Mode", 
    "Slots", 
    "Hubs",
    "Auto open slot when upload under", 
    "Are you sure", 
    "Ban", 
    "You are being banned because",
    "Resolving hub address", 
    "Resolving of hostname", 
    "has failed", 
    "Check the address please", 
    "resolved successfully", 
    "Running", 
    "Stopped", 
    "&File",
    "Update check failed",
    "New version", 
    "released on", 
    "Changes", 
    "Sorry, no new version available",
    "Total",
    "Logged", 
    "Closing", 
    "Logging", 
    "Script started", 
    "Load script",
    "Save script",
    "Full banned",
    "Nick ban", 
    "IP ban", 
    "Permanent", 
    "Global chat flood detected", 
    "You MyINFO is corrupted", 
    "Fake tag", 
    "has suspicious tag, check him", 
    "Full description", 
    "Pinger from IP", 
    "with nick", 
    "detected", 
    "Please don't flood with GetNickList", 
    "You are being disconnected because", 
    "GetNickList flooding", 
    "GetNickList flooder", 
    "was kicked",
    "was temporary banned", 
    "was banned", 
    "You can't kick yourself", 
    "You are not allowed to kick", 
    "Please don't flood with searches", 
    "Search flooding", 
    "Search flooder", 
    "Sorry minimal allowed search length is", 
    "Sorry maximal allowed search length is", 
    "Please don't flood with MyINFO", 
    "MyINFO flooding", 
    "MyINFO flooder", 
    "Your IP has been banned due to possible brute force attack", 
    "Your ASS is banned", 
    "banned because 3x bad password for nick", 
    "Incorrect password",
    "You are not allowed to redirect", 
    "You are redirected to", 
    "is redirected to", 
    "Sorry this hub not allow pinger checking", 
    "Please don't flood with PM", 
    "PM flooding", 
    "PM flooder", 
    "The message was too long", 
    "Please don't flood chat", 
    "Chat flooding", 
    "Chat flooder", 
    "Your nick contains illegal character", 
    "Please correct it and get back again", 
    "The nick you are using is reserved for someone other", 
    "Change your nick and get back again", 
    "Last password for this user was wrong, you need to wait", 
    "before you try again", 
    "This hub is full", 
    "users online", 
    "You can't drop yourself",
    "You can't gag yourself", 
    "Close", 
    "You can't close yourself", 
    "You are not allowed to close", 
    "was closed by", 
    "was closed", 
    "full", 
    "Description tag", 
    "User without tag action", 
    "Maximum users", 
    "Temp ban time after kick, drop...", 
    "Hub owner email (used for hublist pingers)", 
    "Main redirect address (is used for all redirects where is no address specified)", 
    "Message to send when user is not registered", 
    "Passive search replies limit",
    "Operator chat bot", 
    "Temporary ban redirect address", 
    "Permanent ban redirect address", 
    "New connections from single IP limit", 
    "Private message limit to one user from multiple nicks", 
    "Deflood temp ban time", 
    "Maximal hubs limit", 
    "Slot limits", 
    "Hub / slot ratio limit", 
    "Share limits", 
    "Experts only", 
    "Password protection", 
    "Hub startup and tray icon", 
    "Hub commands", 
    "Scripting", 
    "Kick messages", 
    "Status messages", 
    "Pinger", 
    "Allow only registered users", 
    "Enable -->", 
    "Enable and register this bot on hub", 
    "seconds", 
    "Minimum", 
    "Maximum", 
    "Maximal messages to one user per minute", 
    "/ 10 seconds", 
    "Temporary ban time", 
    "Prefixes for hub commands",
    "General settings", 
    "MOTD", 
    "Default bots", 
    "More general", 
    "Ban handling", 
    "Advanced", 
    "More rules",
    "More deflood", 
    "Settings", 
    "More address like dreamland.gotdns.org;zengeday.sytes.net;hublist.zapto.org", 
    "Need hub restart to apply!", 
    "Use %[min] for min share and %[max] for max share.", 
    "Use %[min] for min length and %[max] for max length.", 
    "Use %[hubs] for hubs and %[slots] for slots.", 
    "Use %[min] for min slots and %[max] for max slots.", 
    "Use %[hubs] for hubs.", 
    "When no address is specified then is used main redirect address", 
    "0 = Unlimited", 
    "Bans",
    "Range bans", 
    "Settings saved.",
    "Open in external editor", 
    "Delete script", 
    "Refresh scripts", 
    "Checking for update...",
    "Accepted connections", 
    "Closed connections", 
    "Active connections", 
    "Users online", 
    "Received", 
    "Sent", 
    "Users peak", 
    "Profile name contains not allowed characters (|, space, white chars)", 
    "Full ban", 
    "Created by", 
    "Temporary", 
    "For nick ban must be nick specified!",
    "For IP ban must be IP specified!",
    "is not valid IP address!", 
    "Bad time specified. With that time, the ban would already have expired!", 
    "Similar ban already exist!", 
    "You can't create ban if you don't ban nick or IP!", 
    "Range ban",
    "No valid TCP port specified!",
    "was disconnected", 
    "Please don't flood with same searches", 
    "Same search flooding", 
    "Same search flooder", 
    "Please don't flood with same PM", 
    "Same PM flooding", 
    "Same PM flooder", 
    "Please don't flood chat with same messages", 
    "Same chat messages flooding", 
    "Same chat messages flooder", 
    "Please don't flood with same multiline PM", 
    "Same multiline PM flooding", 
    "Same multiline PM flooder", 
    "Please don't flood chat with same multiline messages", 
    "Same chat multiline messages flooding", 
    "Same chat multiline messages flooder", 
    "More more deflood", 
    "MyINFO length limit", 
    "Your client send incorrect IP", 
    "in connection request, your real IP is", 
    "in search request, your real IP is", 
    "ConnectToMe", 
    "No ConnectToMe deflood", 
    "Please don't flood with ConnectToMe", 
    "ConnectToMe flooding", 
    "ConnectToMe flooder", 
    "RevConnectToMe", 
    "No RevConnectToMe deflood", 
    "Please don't flood with RevConnectToMe", 
    "RevConnectToMe flooding", 
    "RevConnectToMe flooder", 
    "ConnectToMe length limit",
    "RevConnectToMe length limit",
    "Your MyINFO command is too long", 
    "Your ConnectToMe command is too long", 
    "Your RevConnectToMe command is too long", 
    "Search reply", 
    "No search reply deflood", 
    "Please don't flood with search reply", 
    "Search reply flooding", 
    "Search reply flooder", 
    "SR length limit", 
    "Your search reply command is too long", 
    "Received data from user", 
    "No received data deflood", 
    "Please don't flood with data", 
    "Data flooding", 
    "Data flooder", 
    "Interval", 
    "No chat interval", 
    "No private message interval", 
    "No search interval", 
    "Please wait", 
    "seconds before next chat message", 
    "seconds before next private message", 
    "seconds before next search", 
    "Maximum users from same IP", 
    "No maximum users from same IP", 
    "Sorry, the number of maximum connections from your IP has already been reached", 
    "No reconnect time", 
    "Reconnect time", 
    "seconds before reconnect",
    "Rename", 
    "Country", 
    "Save script errors to log", 
    "Sorry, this hub does not allow clients sending buggy $Supports command", 
    "Clients with buggy $Supports command", 
    "Disallow clients sending buggy $Supports command", 
    "Max allowed topic length is 256 characters",
    "Max allowed script name length is 256 characters",
    "Max allowed IP length is 15 characters",
    "&View",
    "&Help",
    "&Exit",
    "&website",
    "&forum",
    "w&iki",
    "&About",
    "&Check for update",
    "&Reload text files",
    "Redirect all users to",
    "Send long MyINFO",
    "Options for short MyINFO",
    "Remove description",
    "Remove tag",
    "Remove connection",
    "Remove email",
    "0 = Disabled",
    "kB",
    "B",
    "KB",
    "MB",
    "GB",
    "TB",
    "&Settings",
    "About",
    "Stats",
    "&Copy",
    "&Select all",
    "&Register user",
    "&Disconnect user",
    "&Kick user",
    "&Ban user",
    "R&edirect user",
    "Please enter reason",
    "was redirected to",
    "Please enter redirect address",
    "Limiter",
    "Scripts errors",
    "Script editor",
    "Open script editor",
    "Failed to open",
    "Open in script editor",
    "Failed to save",
    "Failed to check syntax",
    "Change",
    "Filter registered users",
    "Registered user was deleted. When you now press accept then new registered user will be created!",
    "Registered user was changed.",
    "Add new registered user",
    "Profiles",
    "Add new profile",
    "Profile permissions",
    "Add new ban",
    "Filter bans",
    "Ban was deleted. When you now press accept then new ban will be created!",
    "Add new range ban",
    "Filter range bans",
    "Range ban was deleted. When you now press accept then new range ban will be created!",
    "is available",
    "IPv4 address",
    "IPv6 address",
    "register",
    "as",
    "registered",
    "You were registered, please enter your password",
    "Sorry you are already registered", 
    "Thank you for password, you are now registered as",
    "register user with specified profile. User is asked by hub for password, and after he enter password then is added to regs",
    "in command, hub replaced it with your real IP",
};
//---------------------------------------------------------------------------

#endif
