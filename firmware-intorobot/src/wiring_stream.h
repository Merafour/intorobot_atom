/**
 ******************************************************************************
 * @file     : wiring_stream.h
 * @author   : robin
 * @version	 : V1.0.0
 * @date     : 6-December-2014
 * @brief    :   
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */
#ifndef   WIRING_STREAM_H_
#define   WIRING_STREAM_H_

//#include "Print.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wiring_string.h"
#include "wiring_print.h"
#include "hw_config.h"


// compatability macros for testing
/*
#define   getInt()            parseInt()
#define   getInt(skipChar)    parseInt(skipchar)
#define   getFloat()          parseFloat()
#define   getFloat(skipChar)  parseFloat(skipChar)
#define   getString( pre_string, post_string, buffer, length)
readBytesBetween( pre_string, terminator, buffer, length)
*/

class Stream : public Print
{
    protected:
        system_tick_t _timeout;      // number of milliseconds to wait for the next char before aborting timed read
        system_tick_t _startMillis;  // used for timeout measurement
        int timedRead(void);    // private method to read stream with timeout
        int timedPeek(void);    // private method to peek stream with timeout
        int peekNextDigit(void); // returns the next numeric digit in the stream or -1 if timeout

    public:
        virtual int available(void) = 0;
        virtual int read(void) = 0;
        virtual int peek(void) = 0;
        virtual void flush(void) = 0;

        Stream() {_timeout=100;}

        // parsing methods

        void setTimeout(system_tick_t timeout);  // sets maximum milliseconds to wait for stream data, default is 1 second

        bool find(char *target);   // reads data from the stream until the target string is found
        // returns true if target string is found, false if timed out (see setTimeout)

        bool find(char *target, size_t length);   // reads data from the stream until the target string of given length is found
        // returns true if target string is found, false if timed out

        bool findUntil(char *target, char *terminator);   // as find but search ends if the terminator string is found

        bool findUntil(char *target, size_t targetLen, char *terminate, size_t termLen);   // as above but search ends if the terminate string is found


        long parseInt(void); // returns the first valid (long) integer value from the current position.
        // initial characters that are not digits (or the minus sign) are skipped
        // integer is terminated by the first character that is not a digit.

        float parseFloat(void);               // float version of parseInt

        size_t readBytes( char *buffer, size_t length); // read chars from stream into buffer
        // terminates if length characters have been read or timeout (see setTimeout)
        // returns the number of characters placed in the buffer (0 means no valid data found)

        size_t readBytesUntil( char terminator, char *buffer, size_t length); // as readBytes with terminator character
        // terminates if length characters have been read, timeout, or if the terminator character  detected
        // returns the number of characters placed in the buffer (0 means no valid data found)

        // Arduino String functions to be added here
        String readString(void);
        String readStringUntil(char terminator);

        protected:
        long parseInt(char skipChar); // as above but the given skipChar is ignored
        // as above but the given skipChar is ignored
        // this allows format characters (typically commas) in values to be ignored

        float parseFloat(char skipChar);  // as above but the given skipChar is ignored
};

#endif /*WIRING_STREAM_H_*/

