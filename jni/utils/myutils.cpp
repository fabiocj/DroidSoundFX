/*
 * utils.c
 *
 *  Created on: 30/03/2013
 *      Author: Leonardo
 */

#include "utils/myutils.h"

#include <string.h>
#include <iostream>
#include <android/log.h>
#include <jni.h>

std::string Utils::getSLResultName( SLresult result ) {
	if ( SL_RESULT_SUCCESS == result ) {
		return "SL_RESULT_SUCCESS";
	}
	if ( SL_RESULT_PARAMETER_INVALID == result ) {
		return "SL_RESULT_PARAMETER_INVALID";
	}
	if (  SL_RESULT_FEATURE_UNSUPPORTED == result  ) {
		return "SL_RESULT_FEATURE_UNSUPPORTED";
	}

	return "Other SL_RESULT";
}

std::string Utils::getJNIVersion(jint jrs) {
	if ( jrs == JNI_VERSION_1_1 ) {
		return "1.1";
	}
	if ( jrs == JNI_VERSION_1_2 ) {
		return "1.2";
	}
	if ( jrs == JNI_VERSION_1_4 ) {
		return "1.4";
	}
	if ( jrs == JNI_VERSION_1_6 ) {
		return "1.6";
	}

	return "OTHER VERSION";
}

std::string Utils::getJNIResultName( jint jrs ) {
	if ( jrs == JNI_ABORT ) {
		return "JNI_ABORT";
	}
	if ( jrs == JNI_COMMIT ) { // jrs == JNI_TRUE
		return "JNI_COMMIT || JNI_TRUE";
	}
	if ( jrs == JNI_EDETACHED ) {
		return "JNI_EDETACHED";
	}
	if ( jrs == JNI_ERR ) {
		return "JNI_ERR";
	}
	if ( jrs == JNI_EVERSION ) {
		return "JNI_EVERSION";
	}
	if ( jrs == JNI_FALSE) { // jrs == JNI_OK
		return "JNI_FALSE || JNI_OK";
	}

	return "OTHER JNI RESULT";
}

std::string Utils::getSLInterfaceIdName( SLInterfaceID interfaceId ) {
	if ( SL_IID_3DCOMMIT == interfaceId ) {
		return "SL_IID_3DCOMMIT";
	}
	if ( SL_IID_3DDOPPLER == interfaceId ) {
		return "SL_IID_3DDOPPLER";
	}
	if ( SL_IID_3DGROUPING == interfaceId ) {
		return "SL_IID_3DGROUPING";
	}
	if ( SL_IID_3DLOCATION == interfaceId ) {
		return "SL_IID_3DLOCATION";
	}
	if ( SL_IID_3DMACROSCOPIC == interfaceId ) {
		return "SL_IID_3DMACROSCOPIC";
	}
	if ( SL_IID_3DSOURCE == interfaceId ) {
		return "SL_IID_3DSOURCE";
	}
	if ( SL_IID_ANDROIDBUFFERQUEUESOURCE == interfaceId ) {
		return "SL_IID_ANDROIDBUFFERQUEUESOURCE";
	}
	if ( SL_IID_ANDROIDCONFIGURATION == interfaceId ) {
		return "SL_IID_ANDROIDCONFIGURATION";
	}
	if ( SL_IID_ANDROIDEFFECT == interfaceId ) {
		return "SL_IID_ANDROIDEFFECT";
	}
	if ( SL_IID_ANDROIDEFFECTCAPABILITIES == interfaceId ) {
		return "SL_IID_ANDROIDEFFECTCAPABILITIES";
	}
	if ( SL_IID_ANDROIDEFFECTSEND == interfaceId ) {
		return "SL_IID_ANDROIDEFFECTSEND";
	}
	if ( SL_IID_ANDROIDSIMPLEBUFFERQUEUE == interfaceId ) {
		return "SL_IID_ANDROIDSIMPLEBUFFERQUEUE";
	}
	if ( SL_IID_AUDIODECODERCAPABILITIES == interfaceId ) {
		return "SL_IID_AUDIODECODERCAPABILITIES";
	}
	if ( SL_IID_AUDIOENCODER == interfaceId ) {
		return "SL_IID_AUDIOENCODER";
	}
	if ( SL_IID_AUDIOENCODERCAPABILITIES == interfaceId ) {
		return "SL_IID_AUDIOENCODERCAPABILITIES";
	}
	if ( SL_IID_AUDIOIODEVICECAPABILITIES == interfaceId ) {
		return "SL_IID_AUDIOIODEVICECAPABILITIES";
	}
	if ( SL_IID_BASSBOOST == interfaceId ) {
		return "SL_IID_BASSBOOST";
	}
	if ( SL_IID_BUFFERQUEUE == interfaceId ) {
		return "SL_IID_BUFFERQUEUE";
	}
	if ( SL_IID_DEVICEVOLUME == interfaceId ) {
		return "SL_IID_DEVICEVOLUME";
	}
	if ( SL_IID_DYNAMICINTERFACEMANAGEMENT == interfaceId ) {
		return "SL_IID_DYNAMICINTERFACEMANAGEMENT";
	}
	if ( SL_IID_DYNAMICSOURCE == interfaceId ) {
		return "SL_IID_DYNAMICSOURCE";
	}
	if ( SL_IID_EFFECTSEND == interfaceId ) {
		return "SL_IID_EFFECTSEND";
	}
	if ( SL_IID_ENGINE == interfaceId ) {
		return "SL_IID_ENGINE";
	}
	if ( SL_IID_ENGINECAPABILITIES == interfaceId ) {
		return "SL_IID_ENGINECAPABILITIES";
	}
	if ( SL_IID_ENVIRONMENTALREVERB == interfaceId ) {
		return "SL_IID_ENVIRONMENTALREVERB";
	}
	if ( SL_IID_EQUALIZER == interfaceId ) {
		return "SL_IID_EQUALIZER";
	}
	if ( SL_IID_LED == interfaceId ) {
		return "SL_IID_LED";
	}
	if ( SL_IID_METADATAEXTRACTION == interfaceId ) {
		return "SL_IID_METADATAEXTRACTION";
	}
	if ( SL_IID_METADATATRAVERSAL == interfaceId ) {
		return "SL_IID_METADATATRAVERSAL";
	}
	if ( SL_IID_MIDIMESSAGE == interfaceId ) {
		return "SL_IID_MIDIMESSAGE";
	}
	if ( SL_IID_MIDIMUTESOLO == interfaceId ) {
		return "SL_IID_MIDIMUTESOLO";
	}
	if ( SL_IID_MIDITEMPO == interfaceId ) {
		return "SL_IID_MIDITEMPO";
	}
	if ( SL_IID_MIDITIME == interfaceId ) {
		return "SL_IID_MIDITIME";
	}
	if ( SL_IID_MUTESOLO == interfaceId ) {
		return "SL_IID_MUTESOLO";
	}
	if ( SL_IID_NULL == interfaceId ) {
		return "SL_IID_NULL";
	}
	if ( SL_IID_OBJECT == interfaceId ) {
		return "SL_IID_OBJECT";
	}
	if ( SL_IID_OUTPUTMIX == interfaceId ) {
		return "SL_IID_OUTPUTMIX";
	}
	if ( SL_IID_PITCH == interfaceId ) {
		return "SL_IID_PITCH";
	}
	if ( SL_IID_PLAY == interfaceId ) {
		return "SL_IID_PLAY";
	}
	if ( SL_IID_PLAYBACKRATE == interfaceId ) {
		return "SL_IID_PLAYBACKRATE";
	}
	if ( SL_IID_PREFETCHSTATUS == interfaceId ) {
		return "SL_IID_PREFETCHSTATUS";
	}
	if ( SL_IID_PRESETREVERB == interfaceId ) {
		return "SL_IID_PRESETREVERB";
	}
	if ( SL_IID_RATEPITCH == interfaceId ) {
		return "SL_IID_RATEPITCH";
	}
	if ( SL_IID_RECORD == interfaceId ) {
		return "SL_IID_RECORD";
	}
	if ( SL_IID_SEEK == interfaceId ) {
		return "SL_IID_SEEK";
	}
	if ( SL_IID_THREADSYNC == interfaceId ) {
		return "SL_IID_THREADSYNC";
	}
	if ( SL_IID_VIBRA == interfaceId ) {
		return "SL_IID_VIBRA";
	}
	if ( SL_IID_VIRTUALIZER == interfaceId ) {
		return "SL_IID_VIRTUALIZER";
	}
	if ( SL_IID_VISUALIZATION == interfaceId ) {
		return "SL_IID_VISUALIZATION";
	}
	if ( SL_IID_VOLUME == interfaceId ) {
		return "SL_IID_VOLUME";
	}

	return "OTHER INTERFACE IID";
}

