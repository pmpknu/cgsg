/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shd.h
 * PURPOSE     : Animation project.
 *               Render system.
 *               Shader resource handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 26.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __shd_h_
#define __shd_h_

#include <string>
#include <fstream>

#include "../../def.h"
#include "res.h"

/* Project namespace */

namespace gogl
{
  /* Shader class */
  class shader
  {
    friend class render;
    friend class shader_manager;
    template<typename entry_type, typename index_type>
    friend class resource_manager;
  private:
    std::string Name; /* Shader filename prefix */

    /* Store log to file function.
     * ARGUMENTS:
     *   - message file prefix, shader name and text:
     *       CHAR *Prefix, *PartName, *Text;
     * RETURNS: None.
     */
    VOID Log( const CHAR *Prefix, const CHAR *PartName, const CHAR *Text )
    {
      CHAR Buf[_MAX_PATH];
      GetCurrentDirectory(sizeof(Buf), Buf);

      std::string s;
      s.copy(Buf, sizeof Buf);
 
      std::ofstream(s + "BIN/SHADERS/~OP{S}30.LOG", std::ios_base::app) <<
        Prefix << PartName << ".GLSL\n" << Text << "\n";
    } /* End of 'Log' function */
  public:
    UINT ProgId;      /* Shader program Id */

    /* Load shader program from .GLSL files function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) load shader program Id.
     */
    INT Load( VOID )
    {
      Free();

      struct
      {
        CHAR *Name; /* Shader file prefix name (e.g. "VERT") */
        INT Type;   /* Shader OpenFL type (e.g. GL_VERTEX_SHADER) */
        INT Id;     /* Obtained shader Id from OpenGL */
      } shd[] =
      {
        {const_cast<CHAR *>("VERT"), GL_VERTEX_SHADER},
        {const_cast<CHAR *>("CTRL"), GL_TESS_CONTROL_SHADER},
        {const_cast<CHAR *>("EVAL"), GL_TESS_EVALUATION_SHADER},
        {const_cast<CHAR *>("GEOM"), GL_GEOMETRY_SHADER},
        {const_cast<CHAR *>("FRAG"), GL_FRAGMENT_SHADER},
      };
      INT NoofS = sizeof(shd) / sizeof(shd[0]), i, res, prg = 0;
      std::string txt;
      BOOL is_ok = TRUE;
      static CHAR Buf[1000];

      for (i = 0; i < NoofS; i++)
      {
        /* Build file name */
        CHAR Buf[_MAX_PATH];
        GetCurrentDirectory(sizeof(Buf), Buf);
  
        std::string
          sBuf = Buf,
          sName = shd[i].Name;

        std::ifstream f(sBuf + "/BIN/SHADERS/" + Name + "/" + sName + ".GLSL");

        /* Load shader text from file */
        txt = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

        if (txt.empty())
        {
          if ((i == 0 || i == NoofS - 1))
          {
            Log((Name + "/").c_str(), shd[i].Name, "Error load file");
            is_ok = FALSE;
            break;
          }
          continue;
        }
        /* Create shader */
        if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
        {
          if ((i == 0 || i == NoofS - 1))
          {
            Log((Name + "/").c_str(), shd[i].Name, "Error create shader");
            is_ok = FALSE;
            break;
          }
          continue;
        }
        /* Attach shader text to shader */
        CHAR *Src = const_cast<CHAR *>(txt.c_str());
        glShaderSource(shd[i].Id, 1, &Src, NULL);

        /* Compile shader */
        glCompileShader(shd[i].Id);
        glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
        if (res != 1)
        {
          glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
          Log((Name + "/").c_str(), shd[i].Name, Buf);
          is_ok = FALSE;
          break;
        }
      }

      /* Create shader program */
      if (is_ok)
      {
        if ((prg = glCreateProgram()) == 0)
        {
          Log((Name + "/").c_str(), "PROG", "Error create program");
          is_ok = FALSE;
        }
        else
        {
          /* Attach shaders to program */
          for (i = 0; i < NoofS; i++)
            if (shd[i].Id != 0)
              glAttachShader(prg, shd[i].Id);
          /* Link shader program */
          glLinkProgram(prg);
          glGetProgramiv(prg, GL_LINK_STATUS, &res);
          if (res != 1)
          {
            glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
            Log((Name + "/").c_str(), "PROG", Buf);
            is_ok = FALSE;
          }
        }
      }

      if (!is_ok)
      {
        /* Delete all created shaders */
        for (i = 0; i < NoofS; i++)
          if (shd[i].Id != 0)
          {
            if (prg)
              glDetachShader(prg, shd[i].Id);
            glDeleteShader(shd[i].Id);
          }
        /* Delete program */
        if (prg)
          glDeleteProgram(prg);
        prg = 0;
      }
      return ProgId = prg;
    } /* End of 'Load' function */

    /* Free shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      UINT shdrs[5];
      INT n, i;

      if (ProgId == 0 || !glIsProgram(ProgId))
        return;

      glGetAttachedShaders(ProgId, 5, &n, shdrs);
      for (i = 0; i < n; i++)
      {
        glDetachShader(ProgId, shdrs[i]);
        glDeleteShader(shdrs[i]);
      }
      glDeleteProgram(ProgId);

      ProgId = 0;
    } /* End of 'Free' function */

    BOOL Apply( VOID )
    {
      if (glIsProgram(ProgId))
        glUseProgram(ProgId);
      else
        return FALSE;
      return TRUE;
    }

    shader( VOID )
    {
    }

    shader( const std::string &ShaderFileNamePrefix )
    {
      Name = ShaderFileNamePrefix;
      ProgId = Load();
    }

    /* Shader uniform value set function.
     * ARGUMENTS:
     *   - uniform name:
     *       const CHAR *Name;
     *   - uniform value:
     *       const value_type &Value;
     * RETURNS: None.
     */
    template<typename value_type>
    VOID UniSet( const CHAR *Name, const value_type &Value )
    {
      INT loc;

      if ((loc = glGetUniformLocation(ProgId, Name)) != -1)
        if constexpr (std::is_convertible_v<FLT, value_type>)
          glUniform1f(loc, Value);
        else if constexpr (std::is_convertible_v<INT, value_type>)
          glUniform1i(loc, Value);
        else if constexpr (std::is_convertible_v<vec3, value_type>)
          glUniform3fv(loc, 1, Value);
        else if constexpr (std::is_convertible_v<matr, value_type>)
          glUniformMatrix4fv(loc, 1, FALSE, Value);
    } /* End of 'UniSet' function */
  }; /* End of 'shader' class */

  /* Shader class */
  class shader_manager : public resource_manager<shader, std::string>
  {
  public:
    /* Reupload shaders function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID )
    {
      for (auto &shd : Stock)
        shd.second.Load();
    } /* End of 'Update' function */

    /* Create shader function.
     * ARGUMENTS:
     *   - file name prefix:
     *       std::string &ShaderFileNamePrefix;
     * RETURNS:
     *   (shader *) shader create interface.
     */
    shader * CreateShd( const std::string &ShaderFileNamePrefix )
    {
      shader *find = {};

      if ((find = Find(ShaderFileNamePrefix)) != nullptr)
        return find;

      return Add(shader(ShaderFileNamePrefix));
    } /* End of 'CreateShd' function */

  }; /* End of 'shader_manager' class */
} /* end of 'gogl' namespace */

#endif /* __shd_h_ */

/* END OF 'shd.h' FILE */