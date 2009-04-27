/*
 * gnote
 *
 * Copyright (C) 2009 Hubert Figuiere
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */




#include "sharp/string.hpp"
#include "sharp/uri.hpp"

#define FILE_URI_SCHEME "file://"

namespace sharp {

  bool Uri::is_file() const
  {
    return string_starts_with(m_uri, FILE_URI_SCHEME);
  }


  std::string Uri::local_path() const
  {
    if(!is_file()) {
      return m_uri;
    }
    return string_replace_first(m_uri, FILE_URI_SCHEME, "");
  }

  std::string Uri::get_host() const
  {
    std::string host;
    
    return host;
  }


  /** this is a very minimalistic implementation */
  std::string Uri::escape_uri_string(const std::string &s)
  {
    return string_replace_all(s, " ", "%20");
  }

}

