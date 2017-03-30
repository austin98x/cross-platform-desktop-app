/* -------------------------------------------------------------------------
//	File name		：	winnls.h
//	Author 			：	Austin
//	Create Time		：	2017-3-30 16:15:11
//	Description 	：	
//
// -----------------------------------------------------------------------*/
#ifndef __WINNLS_H__
#define __WINNLS_H__

//
//  String Flags.
//
#define NORM_IGNORECASE				0x00000001		// ignore case
#define NORM_IGNORENONSPACE			0x00000002		// ignore nonspacing chars
#define NORM_IGNORESYMBOLS			0x00000004		// ignore symbols

#define LINGUISTIC_IGNORECASE		0x00000010		// linguistically appropriate 'ignore case'
#define LINGUISTIC_IGNOREDIACRITIC	0x00000020		// linguistically appropriate 'ignore nonspace'

#define NORM_IGNOREKANATYPE			0x00010000		// ignore kanatype
#define NORM_IGNOREWIDTH			0x00020000		// ignore width
#define NORM_LINGUISTIC_CASING		0x08000000		// use linguistic rules for casing

// -------------------------------------------------------------------------

//
//  Locale Types.
//
//  These types are used for the GetLocaleInfo NLS API routine.
//  Some of these types are also used for the SetLocaleInfo NLS API routine.
//

//
//  The following LCTypes may be used in combination with any other LCTypes.
//
//    LOCALE_NOUSEROVERRIDE is also used in GetTimeFormat and
//    GetDateFormat.
//
//    LOCALE_USE_CP_ACP is used in many of the A (Ansi) apis that need
//    to do string translation.
//
//    LOCALE_RETURN_NUMBER will return the result from GetLocaleInfo as a
//    number instead of a string.  This flag is only valid for the LCTypes
//    beginning with LOCALE_I.
//
#define LOCALE_NOUSEROVERRIDE         0x80000000   // do not use user overrides
#define LOCALE_USE_CP_ACP             0x40000000   // use the system ACP

#if(WINVER >= 0x0400)
#define LOCALE_RETURN_NUMBER          0x20000000   // return number instead of string
#endif /* WINVER >= 0x0400 */

#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_RETURN_GENITIVE_NAMES  0x10000000   //Flag to return the Genitive forms of month names
#define LOCALE_ALLOW_NEUTRAL_NAMES    0x08000000   //Flag to allow returning neutral names/lcids for name conversion
#endif //(WINVER >= _WIN32_WINNT_WIN7)

//
//  The following LCTypes are mutually exclusive in that they may NOT
//  be used in combination with each other.
//

//
// These are the various forms of the name of the locale:
//
#define LOCALE_SLOCALIZEDDISPLAYNAME  0x00000002   // localized name of locale, eg "German (Germany)" in UI language
#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_SENGLISHDISPLAYNAME    0x00000072   // Display name (language + country usually) in English, eg "German (Germany)"
#define LOCALE_SNATIVEDISPLAYNAME     0x00000073   // Display name in native locale language, eg "Deutsch (Deutschland)
#endif //(WINVER >= _WIN32_WINNT_WIN7)

#if (WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SLOCALIZEDLANGUAGENAME 0x0000006f   // Language Display Name for a language, eg "German" in UI language
#endif //(WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SENGLISHLANGUAGENAME   0x00001001   // English name of language, eg "German"
#define LOCALE_SNATIVELANGUAGENAME    0x00000004   // native name of language, eg "Deutsch"

#define LOCALE_SLOCALIZEDCOUNTRYNAME  0x00000006   // localized name of country, eg "Germany" in UI language
#define LOCALE_SENGLISHCOUNTRYNAME    0x00001002   // English name of country, eg "Germany"
#define LOCALE_SNATIVECOUNTRYNAME     0x00000008   // native name of country, eg "Deutschland"

//
// Legacy labels for the locale name values
//
#define LOCALE_SLANGUAGE              0x00000002   // localized name of locale, eg "German (Germany)" in UI language
#if (WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SLANGDISPLAYNAME       0x0000006f   // Language Display Name for a language, eg "German" in UI language
#endif //(WINVER >= _WIN32_WINNT_VISTA)
#define LOCALE_SENGLANGUAGE           0x00001001   // English name of language, eg "German"
#define LOCALE_SNATIVELANGNAME        0x00000004   // native name of language, eg "Deutsch"
#define LOCALE_SCOUNTRY               0x00000006   // localized name of country, eg "Germany" in UI language
#define LOCALE_SENGCOUNTRY            0x00001002   // English name of country, eg "Germany"
#define LOCALE_SNATIVECTRYNAME        0x00000008   // native name of country, eg "Deutschland"

// Additional LCTypes
#define LOCALE_ILANGUAGE              0x00000001   // language id, LOCALE_SNAME preferred

#define LOCALE_SABBREVLANGNAME        0x00000003   // arbitrary abbreviated language name, LOCALE_SISO639LANGNAME preferred

#define LOCALE_ICOUNTRY               0x00000005   // country code, eg 1, LOCALE_SISO3166CTRYNAME may be more useful.
#define LOCALE_SABBREVCTRYNAME        0x00000007   // arbitrary abbreviated country name, LOCALE_SISO3166CTRYNAME preferred
#define LOCALE_IGEOID                 0x0000005B   // geographical location id, eg "244"

#define LOCALE_IDEFAULTLANGUAGE       0x00000009   // default language id, deprecated
#define LOCALE_IDEFAULTCOUNTRY        0x0000000A   // default country code, deprecated
#define LOCALE_IDEFAULTCODEPAGE       0x0000000B   // default oem code page (use of Unicode is recommended instead)
#define LOCALE_IDEFAULTANSICODEPAGE   0x00001004   // default ansi code page (use of Unicode is recommended instead)
#define LOCALE_IDEFAULTMACCODEPAGE    0x00001011   // default mac code page (use of Unicode is recommended instead)

#define LOCALE_SLIST                  0x0000000C   // list item separator, eg "," for "1,2,3,4"
#define LOCALE_IMEASURE               0x0000000D   // 0 = metric, 1 = US measurement system

#define LOCALE_SDECIMAL               0x0000000E   // decimal separator, eg "." for 1,234.00
#define LOCALE_STHOUSAND              0x0000000F   // thousand separator, eg "," for 1,234.00
#define LOCALE_SGROUPING              0x00000010   // digit grouping, eg "3;0" for 1,000,000
#define LOCALE_IDIGITS                0x00000011   // number of fractional digits eg 2 for 1.00
#define LOCALE_ILZERO                 0x00000012   // leading zeros for decimal, 0 for .97, 1 for 0.97
#define LOCALE_INEGNUMBER             0x00001010   // negative number mode, 0-4, see documentation
#define LOCALE_SNATIVEDIGITS          0x00000013   // native digits for 0-9, eg "0123456789"

#define LOCALE_SCURRENCY              0x00000014   // local monetary symbol, eg "$"
#define LOCALE_SINTLSYMBOL            0x00000015   // intl monetary symbol, eg "USD"
#define LOCALE_SMONDECIMALSEP         0x00000016   // monetary decimal separator, eg "." for $1,234.00
#define LOCALE_SMONTHOUSANDSEP        0x00000017   // monetary thousand separator, eg "," for $1,234.00
#define LOCALE_SMONGROUPING           0x00000018   // monetary grouping, eg "3;0" for $1,000,000.00
#define LOCALE_ICURRDIGITS            0x00000019   // # local monetary digits, eg 2 for $1.00
#define LOCALE_IINTLCURRDIGITS        0x0000001A   // # intl monetary digits, eg 2 for $1.00
#define LOCALE_ICURRENCY              0x0000001B   // positive currency mode, 0-3, see documenation
#define LOCALE_INEGCURR               0x0000001C   // negative currency mode, 0-15, see documentation

#define LOCALE_SDATE                  0x0000001D   // date separator (derived from LOCALE_SSHORTDATE, use that instead)
#define LOCALE_STIME                  0x0000001E   // time separator (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_SSHORTDATE             0x0000001F   // short date format string, eg "MM/dd/yyyy"
#define LOCALE_SLONGDATE              0x00000020   // long date format string, eg "dddd, MMMM dd, yyyy"
#define LOCALE_STIMEFORMAT            0x00001003   // time format string, eg "HH:mm:ss"
#define LOCALE_IDATE                  0x00000021   // short date format ordering (derived from LOCALE_SSHORTDATE, use that instead)
#define LOCALE_ILDATE                 0x00000022   // long date format ordering (derived from LOCALE_SLONGDATE, use that instead)
#define LOCALE_ITIME                  0x00000023   // time format specifier (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_ITIMEMARKPOSN          0x00001005   // time marker position (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_ICENTURY               0x00000024   // century format specifier (short date, LOCALE_SSHORTDATE is preferred)
#define LOCALE_ITLZERO                0x00000025   // leading zeros in time field (derived from LOCALE_STIMEFORMAT, use that instead)
#define LOCALE_IDAYLZERO              0x00000026   // leading zeros in day field (short date, LOCALE_SSHORTDATE is preferred)
#define LOCALE_IMONLZERO              0x00000027   // leading zeros in month field (short date, LOCALE_SSHORTDATE is preferred)
#define LOCALE_S1159                  0x00000028   // AM designator, eg "AM"
#define LOCALE_S2359                  0x00000029   // PM designator, eg "PM"

#define LOCALE_ICALENDARTYPE          0x00001009   // type of calendar specifier, eg CAL_GREGORIAN
#define LOCALE_IOPTIONALCALENDAR      0x0000100B   // additional calendar types specifier, eg CAL_GREGORIAN_US
#define LOCALE_IFIRSTDAYOFWEEK        0x0000100C   // first day of week specifier, 0-6, 0=Monday, 6=Sunday
#define LOCALE_IFIRSTWEEKOFYEAR       0x0000100D   // first week of year specifier, 0-2, see documentation

#define LOCALE_SDAYNAME1              0x0000002A   // long name for Monday
#define LOCALE_SDAYNAME2              0x0000002B   // long name for Tuesday
#define LOCALE_SDAYNAME3              0x0000002C   // long name for Wednesday
#define LOCALE_SDAYNAME4              0x0000002D   // long name for Thursday
#define LOCALE_SDAYNAME5              0x0000002E   // long name for Friday
#define LOCALE_SDAYNAME6              0x0000002F   // long name for Saturday
#define LOCALE_SDAYNAME7              0x00000030   // long name for Sunday
#define LOCALE_SABBREVDAYNAME1        0x00000031   // abbreviated name for Monday
#define LOCALE_SABBREVDAYNAME2        0x00000032   // abbreviated name for Tuesday
#define LOCALE_SABBREVDAYNAME3        0x00000033   // abbreviated name for Wednesday
#define LOCALE_SABBREVDAYNAME4        0x00000034   // abbreviated name for Thursday
#define LOCALE_SABBREVDAYNAME5        0x00000035   // abbreviated name for Friday
#define LOCALE_SABBREVDAYNAME6        0x00000036   // abbreviated name for Saturday
#define LOCALE_SABBREVDAYNAME7        0x00000037   // abbreviated name for Sunday
#define LOCALE_SMONTHNAME1            0x00000038   // long name for January
#define LOCALE_SMONTHNAME2            0x00000039   // long name for February
#define LOCALE_SMONTHNAME3            0x0000003A   // long name for March
#define LOCALE_SMONTHNAME4            0x0000003B   // long name for April
#define LOCALE_SMONTHNAME5            0x0000003C   // long name for May
#define LOCALE_SMONTHNAME6            0x0000003D   // long name for June
#define LOCALE_SMONTHNAME7            0x0000003E   // long name for July
#define LOCALE_SMONTHNAME8            0x0000003F   // long name for August
#define LOCALE_SMONTHNAME9            0x00000040   // long name for September
#define LOCALE_SMONTHNAME10           0x00000041   // long name for October
#define LOCALE_SMONTHNAME11           0x00000042   // long name for November
#define LOCALE_SMONTHNAME12           0x00000043   // long name for December
#define LOCALE_SMONTHNAME13           0x0000100E   // long name for 13th month (if exists)
#define LOCALE_SABBREVMONTHNAME1      0x00000044   // abbreviated name for January
#define LOCALE_SABBREVMONTHNAME2      0x00000045   // abbreviated name for February
#define LOCALE_SABBREVMONTHNAME3      0x00000046   // abbreviated name for March
#define LOCALE_SABBREVMONTHNAME4      0x00000047   // abbreviated name for April
#define LOCALE_SABBREVMONTHNAME5      0x00000048   // abbreviated name for May
#define LOCALE_SABBREVMONTHNAME6      0x00000049   // abbreviated name for June
#define LOCALE_SABBREVMONTHNAME7      0x0000004A   // abbreviated name for July
#define LOCALE_SABBREVMONTHNAME8      0x0000004B   // abbreviated name for August
#define LOCALE_SABBREVMONTHNAME9      0x0000004C   // abbreviated name for September
#define LOCALE_SABBREVMONTHNAME10     0x0000004D   // abbreviated name for October
#define LOCALE_SABBREVMONTHNAME11     0x0000004E   // abbreviated name for November
#define LOCALE_SABBREVMONTHNAME12     0x0000004F   // abbreviated name for December
#define LOCALE_SABBREVMONTHNAME13     0x0000100F   // abbreviated name for 13th month (if exists)

#define LOCALE_SPOSITIVESIGN          0x00000050   // positive sign, eg ""
#define LOCALE_SNEGATIVESIGN          0x00000051   // negative sign, eg "-"
#define LOCALE_IPOSSIGNPOSN           0x00000052   // positive sign position (derived from INEGCURR)
#define LOCALE_INEGSIGNPOSN           0x00000053   // negative sign position (derived from INEGCURR)
#define LOCALE_IPOSSYMPRECEDES        0x00000054   // mon sym precedes pos amt (derived from ICURRENCY)
#define LOCALE_IPOSSEPBYSPACE         0x00000055   // mon sym sep by space from pos amt (derived from ICURRENCY)
#define LOCALE_INEGSYMPRECEDES        0x00000056   // mon sym precedes neg amt (derived from INEGCURR)
#define LOCALE_INEGSEPBYSPACE         0x00000057   // mon sym sep by space from neg amt (derived from INEGCURR)

#if(WINVER >= 0x0400)
#define LOCALE_FONTSIGNATURE          0x00000058   // font signature
#define LOCALE_SISO639LANGNAME        0x00000059   // ISO abbreviated language name, eg "en"
#define LOCALE_SISO3166CTRYNAME       0x0000005A   // ISO abbreviated country name, eg "US"
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define LOCALE_IDEFAULTEBCDICCODEPAGE 0x00001012   // default ebcdic code page (use of Unicode is recommended instead)
#define LOCALE_IPAPERSIZE             0x0000100A   // 1 = letter, 5 = legal, 8 = a3, 9 = a4
#define LOCALE_SENGCURRNAME           0x00001007   // english name of currency, eg "Euro"
#define LOCALE_SNATIVECURRNAME        0x00001008   // native name of currency, eg "euro"
#define LOCALE_SYEARMONTH             0x00001006   // year month format string, eg "MM/yyyy"
#define LOCALE_SSORTNAME              0x00001013   // sort name, usually "", eg "Dictionary" in UI Language
#define LOCALE_IDIGITSUBSTITUTION     0x00001014   // 0 = context, 1 = none, 2 = national

#endif /* WINVER >= 0x0500 */

#if (WINVER >= 0x0600)
#define LOCALE_SNAME                  0x0000005c   // locale name (ie: en-us)
#define LOCALE_SDURATION              0x0000005d   // time duration format, eg "hh:mm:ss"
#define LOCALE_SKEYBOARDSTOINSTALL    0x0000005e   // Used internally, see GetKeyboardLayoutName() function
#define LOCALE_SSHORTESTDAYNAME1      0x00000060   // Shortest day name for Monday
#define LOCALE_SSHORTESTDAYNAME2      0x00000061   // Shortest day name for Tuesday
#define LOCALE_SSHORTESTDAYNAME3      0x00000062   // Shortest day name for Wednesday
#define LOCALE_SSHORTESTDAYNAME4      0x00000063   // Shortest day name for Thursday
#define LOCALE_SSHORTESTDAYNAME5      0x00000064   // Shortest day name for Friday
#define LOCALE_SSHORTESTDAYNAME6      0x00000065   // Shortest day name for Saturday
#define LOCALE_SSHORTESTDAYNAME7      0x00000066   // Shortest day name for Sunday
#define LOCALE_SISO639LANGNAME2       0x00000067   // 3 character ISO abbreviated language name, eg "eng"
#define LOCALE_SISO3166CTRYNAME2      0x00000068   // 3 character ISO country name, eg "USA"
#define LOCALE_SNAN                   0x00000069   // Not a Number, eg "NaN"
#define LOCALE_SPOSINFINITY           0x0000006a   // + Infinity, eg "infinity"
#define LOCALE_SNEGINFINITY           0x0000006b   // - Infinity, eg "-infinity"
#define LOCALE_SSCRIPTS               0x0000006c   // Typical scripts in the locale: ; delimited script codes, eg "Latn;"
#define LOCALE_SPARENT                0x0000006d   // Fallback name for resources, eg "en" for "en-US"
#define LOCALE_SCONSOLEFALLBACKNAME   0x0000006e   // Fallback name for within the console for Unicode Only locales, eg "en" for bn-IN
#endif //(WINVER >= 0x0600)

#if (WINVER >= _WIN32_WINNT_WIN7)
#define LOCALE_IREADINGLAYOUT         0x00000070   // Returns one of the following 4 reading layout values:
                                                   // 0 - Left to right (eg en-US)
                                                   // 1 - Right to left (eg arabic locales)
                                                   // 2 - Vertical top to bottom with columns to the left and also left to right (ja-JP locales)
                                                   // 3 - Vertical top to bottom with columns proceeding to the right
#define LOCALE_INEUTRAL               0x00000071   // Returns 0 for specific cultures, 1 for neutral cultures.
#define LOCALE_INEGATIVEPERCENT       0x00000074   // Returns 0-11 for the negative percent format
#define LOCALE_IPOSITIVEPERCENT       0x00000075   // Returns 0-3 for the positive percent formatIPOSITIVEPERCENT
#define LOCALE_SPERCENT               0x00000076   // Returns the percent symbol
#define LOCALE_SPERMILLE              0x00000077   // Returns the permille (U+2030) symbol
#define LOCALE_SMONTHDAY              0x00000078   // Returns the preferred month/day format
#define LOCALE_SSHORTTIME             0x00000079   // Returns the preferred short time format (ie: no seconds, just h:mm)
#define LOCALE_SOPENTYPELANGUAGETAG   0x0000007a   // Open type language tag, eg: "latn" or "dflt"
#define LOCALE_SSORTLOCALE            0x0000007b   // Name of locale to use for sorting/collation/casing behavior.
#endif //(WINVER >= _WIN32_WINNT_WIN7)

#define CSTR_LESS_THAN            1           // string 1 less than string 2
#define CSTR_EQUAL                2           // string 1 equal to string 2
#define CSTR_GREATER_THAN         3           // string 1 greater than string 2

#endif /* __WINNLS_H__ */
