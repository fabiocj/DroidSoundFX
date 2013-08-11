/*
 * utils.h
 *
 *  Created on: 30/03/2013
 *      Author: Leonardo
 */

#ifndef UTILS_H_
#define UTILS_H_

// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string.h>
#include <iostream>
#include <jni.h>

#include <android/log.h>

#define  LOG_TAG    "SoundCore"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

class Utils {

public:

	static std::string getSLInterfaceIdName( SLInterfaceID );
	static std::string getSLResultName( SLresult );

	static std::string getJNIResultName( jint );
	static std::string getJNIVersion( jint );


};

#endif /* UTILS_H_ */
