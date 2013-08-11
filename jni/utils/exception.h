/*
 * exception.h
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

/*
 * exception
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#include "exception.h"
#include <jni.h>
#include <string>

namespace DroidSoundFX {

	class Exception {

		public:

			static jint throwNoClassDefError( JNIEnv *env, std::string message );

			//static jint throwNoSuchMethodError( JNIEnv *env, std::string className, std::string methodName, std::string signature );

			static jint throwNoSuchFieldError( JNIEnv *env, std::string message );

			static jint throwOutOfMemoryError( JNIEnv *env, std::string message );

			static jint throwException( JNIEnv *env, std::string  message );

	};
}

#endif /* EXCEPTION_H_ */
