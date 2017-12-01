/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#include <AuroraFW/GEngine/GL/Program.h>
#include <AuroraFW/CLI/Log.h>

namespace AuroraFW {
	namespace GEngine {
		GLProgram::GLProgram()
			: _program(glCreateProgram())
		{}

		GLuint GLProgram::generate()
		{
			GLCall(glLinkProgram(_program));
			GLint isLinked = 0;
			GLCall(glGetProgramiv(_program, GL_LINK_STATUS, (int *)&isLinked));
			if(isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				GLCall(glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength));

				//The maxLength includes the NULL character
				GLchar* errorLog = static_cast<GLchar*>(malloc(maxLength));
				GLCall(glGetProgramInfoLog(_program, maxLength, &maxLength, errorLog));
				CLI::Log(CLI::Error, errorLog);
				free(errorLog);

				GLCall(glDeleteProgram(_program));

				//Use the infoLog as you see fit.
			}
			GLCall(glValidateProgram(_program));
		}
	}
}