#ifndef STR_UTIL_H
#define STR_UTIL_H


/**
*Determine whether it is a Windows system
* @param void
*Is @ return boolean a Windows system
*/
_Bool is_windows_sys();

/**
*Determine if the file exists
*The file path of @ aram file_math, for example: "./assets/images/cymbal/cymbal-00. jpg";
*Does the @ return boolean file exist
*/
_Bool is_file_exist(const char *file_path);

#endif
