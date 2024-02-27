/******************************************************************************
 * Protocce Engine                                                            *
 * Part of the Crown and Cutlass Project                                      *
 * http://www.crownandcutlass.com                                             *
 * Copyright (c) 2004 - 2007 David Thulson and Collin Sanford                 *
 * All rights reserved.                                                       *
 *                                                                            *
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 * 1. Redistributions of source code must retain the above copyright          *
 *    notice, this list of conditions and the following disclaimer.           *
 * 2. Redistributions in binary form must reproduce the above copyright       *
 *    notice, this list of conditions and the following disclaimer in the     *
 *    documentation and/or other materials provided with the distribution.    *
 * 3. The names of the authors may not be used to endorse or promote products *
 *    derived from this software without specific prior written permission.   *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR       *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.    *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,           *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT   *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF   *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.          *
 *                                                                            *
 ******************************************************************************/

#ifndef _PCCE_SOUNDUTIL_H_

#define _PCCE_SOUNDUTIL_H_

#include <string>
#include <AL/al.h>
#include <AL/alc.h>

namespace pcce {

  /// Initialize OpenAL
  void InitializeAL();

  /// Shutdown OpenAL
  void ShutdownAL();

  /// Load a wave file into buffer
  ALuint LoadWav(const std::string& fileName);

  ALuint GenSource();
  ALuint GenSource(ALuint buffer);

  void ClearALError();
  const std::string& GetALErrorStr(const ALenum error);

  #define PCCE_AL_CHECK() { ALenum error = alGetError(); pcce::check< pcce::Exception >(AL_NO_ERROR == error, GetALErrorStr(error), __FILE__, __LINE__); }
}

#endif
