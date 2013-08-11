/*
 * exception
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#include "exception.h"
#include <jni.h>
#include <stdlib.h>
#include <string>

namespace DroidSoundFX {

		jint Exception::throwNoClassDefError( JNIEnv *env, std::string message ) {
			jclass		 exClass;
			char		*className = "java/lang/NoClassDefFoundError" ;

			exClass = env->FindClass( className );
			if ( exClass == NULL )
				return Exception::throwNoClassDefError( env, className );

			return env->ThrowNew( exClass, message.c_str() );
		}
		/*
		jint Exception::throwNoSuchMethodError( JNIEnv *env, char *className, char *methodName, char *signature ) {
			jclass		 exClass;
			char		*exClassName = "java/lang/NoSuchMethodError" ;
			LPTSTR		 msgBuf;
			jint		 retCode;
			size_t		 nMallocSize;

			exClass = env->FindClass( exClassName );
			if ( exClass == NULL )
				return throwNoClassDefError( exClassName );

			nMallocSize = strlen(className)
				+ strlen(methodName)
				+ strlen(signature) + 8;

			msgBuf = malloc( nMallocSize );
			if ( msgBuf == NULL )
				return throwOutOfMemoryError( "throwNoSuchMethodError: allocating msgBuf" );

			memset( msgBuf, 0, nMallocSize );

			strcpy( msgBuf, className );
			strcat( msgBuf, "." );
			strcat( msgBuf, methodName );
			strcat( msgBuf, "." );
			strcat( msgBuf, signature );

			retCode = env->ThrowNew( exClass, msgBuf );
			free ( msgBuf );
			return retCode;
		}
		*/

		jint Exception::throwNoSuchFieldError( JNIEnv *env, std::string message ) {
			jclass		 exClass;
			char		*className = "java/lang/NoSuchFieldError" ;

			exClass = env->FindClass( className );
			if ( exClass == NULL )
				return Exception::throwNoClassDefError( env, className );

			return env->ThrowNew( exClass, message.c_str() );
		}

		jint Exception::throwOutOfMemoryError( JNIEnv *env, std::string message ) {
			jclass		 exClass;
			char		*className = "java/lang/OutOfMemoryError" ;

			exClass = env->FindClass( className );
			if ( exClass == NULL )
				return Exception::throwNoClassDefError( env, className );

			return env->ThrowNew( exClass, message.c_str() );
		}

		jint Exception::throwException( JNIEnv *env, std::string message ) {
			jclass		 exClass;
			char		*className = "java/lang/Exception" ;

			exClass = env->FindClass( className );
			if ( exClass == NULL )
				return Exception::throwNoClassDefError( env, className );


			return env->ThrowNew( exClass, message.c_str() );
		}

}


