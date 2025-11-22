/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;

namespace Harlinn.Hydrology
{
    public enum ParseError
    {
        /// <summary>
        /// Corrupt file
        /// </summary>
        PARSE_BAD,
        /// <summary>
        /// Not enough parameters
        /// </summary>
        PARSE_NOT_ENOUGH,
        /// <summary>
        /// Too many parameters
        /// </summary>
        PARSE_TOO_MANY,
        /// <summary>
        /// No error
        /// </summary>
        PARSE_GOOD,
        /// <summary>
        /// End of file error
        /// </summary>
        PARSE_EOF
    }


    /// <summary>
    /// Parses data from file
    /// </summary>
    public class Parser
    {
        /// <summary>
        /// maximum delimited input items per line
        /// </summary>
        public const int MAXINPUTITEMS = 500;
        /// <summary>
        /// maximum characters in line
        /// </summary>
        public const int MAXCHARINLINE = 6000;
        /// <summary>
        /// turn to true for debugging of parser
        /// </summary>
        public const bool parserdebug = false;

        /// <summary>
        /// current input
        /// </summary>
        TextReader _input;
        /// <summary>
        /// current line in input file
        /// </summary>
        int _lineno;
        /// <summary>
        /// current input filename
        /// </summary>
        string _filename;
        /// <summary>
        /// true if spaces & tabs ignored in tokenization
        /// </summary>
        bool _comma_only;
        /// <summary>
        /// true if currently parsing math exp (commas not ignored)
        /// </summary>
        bool _parsing_math_exp;


        public Parser(TextReader input, int lineno = 0, string filename = "")
        {
            _input = input;
            _lineno = lineno;
            _filename = filename;
        }

        public string? ReadLine()
        {
            var result = _input.ReadLine();
            _lineno += result != null ? 1 : 0;
            return result;
        }


        bool TryTokenize(out string[] tokens)
        {
            var line = ReadLine();
            if (string.IsNullOrWhiteSpace(line))
            {
                tokens = new string[0];
                return false;
            }
            tokens = [];
            return false;

        }
            /*
            static char wholeline[MAXCHARINLINE];
            static char* tempwordarray[MAXINPUTITEMS];
            char* p;
            int ct(0),w;
            char delimiters[6];
            delimiters[0] = ' '; //space
            delimiters[1] = '\t';//tab
            delimiters[2] = ','; //comma
            delimiters[3] = '\r';//carriage return (ignored in visual c++)
            delimiters[4] = '\n';//newline -necc?
            delimiters[5] = '\0';//last delimiter
            if (_comma_only)
            {
                delimiters[0] = delimiters[1] = ',';
            }
            if (_parsing_math_exp)
            {
                delimiters[2] = ' ';//don't use commas
            }
  (*wholeline) = 0;
            if (_INPUT->eof()) { return true; }
            _INPUT->getline(wholeline, MAXCHARINLINE);            //get entire line as 1 string
            if (_INPUT->fail())
            {
                return true; //handles blank line peeked at end of file (for some reason)
                             //cout<<"failed: "<<filename<<" line "<<l<<"|"<<wholeline<<"|"<<INPUT->ios::eofbit<<endl;
                             //ExitGracefully("Too many characters in line or (maybe) using Mac-style carriage return line endings.",BAD_DATA);
            }

            _lineno++;
            if ((parserdebug) && ((*wholeline) != 0)) { cout << wholeline << endl; }

            if ((*wholeline) == 0)
            {
                numwords = 0;
                return false;
            }

            if (_parsing_math_exp)
            {
                string line;
                line = AddSpacesBeforeOps(wholeline);
                strcpy(wholeline, line.c_str());
                _parsing_math_exp = false;
            }

            p = strtok(wholeline, delimiters);
            while (p)
            {                                         //sift through words, place in temparray, count line length
                tempwordarray[ct] = p;
                //p=strtok_s(NULL, delimiters,&junk);
                p = strtok(NULL, delimiters);
                ct++;
                if ((p != NULL) && (p[0] == '#')) { break; } //ignore all content after '#'
            }
            for (w = 0; w < ct; w++)
            {                              //copy temp array of words into out[]
                if (w > MAXINPUTITEMS)
                {
                    numwords = ct;
                    string warn = "Tokenizeline:: exceeded maximum number of items in single line in file " + _filename;
                    ExitGracefully(warn.c_str(), BAD_DATA);
                    return true;
                }
    out[w] = tempwordarray[w];
                //cout<<out[w]<<"|";
            }
            //cout <<endl;
            numwords = ct;
            return false;
            */
        





    }






}
