using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

using Harlinn.MSSql.Tool.CodeGenerators;

namespace Harlinn.MSSql.Tool.Output
{
    public class CodeWriter
    {
        private StringBuilder builder_;
        private int indentLevel_;
        private bool atStartOfLine_ = true;
        readonly Context _context;

        

        public CodeWriter(Context context)
        {
            builder_ = new StringBuilder();
            indentLevel_ = 0;
            _context = context;
        }
        public Context Context => _context;

        public BuildOptions BuildOptions => (BuildOptions)Context.Options;
        public bool UseWrappers => BuildOptions.UseWrappers;

        public void IncreaseIndent()
        {
            indentLevel_++;
        }
        public void DecreaseIndent()
        {
            if (indentLevel_ > 0)
            {
                indentLevel_--;
            }
        }
        public void WriteLine(string line)
        {
            if (atStartOfLine_)
            {
                if (string.IsNullOrEmpty(line) == false)
                {
                    builder_.Append(new string(' ', indentLevel_ * 4));
                }
            }
            builder_.AppendLine(line);
            atStartOfLine_ = false;
        }

        public void WriteLine()
        {
            builder_.AppendLine();
            atStartOfLine_ = true;
        }

        public void WriteLine(string format, params object[] args)
        {
            var line = string.Format(System.Globalization.CultureInfo.InvariantCulture,format, args);
            WriteLine(line);
        }


        public void Write(string line)
        {
            if (atStartOfLine_)
            {
                builder_.Append(new string(' ', indentLevel_ * 4));
                atStartOfLine_ = false;
            }
            builder_.Append(line);
        }

        public void Write(string format, params object[] args)
        {
            var line = string.Format(System.Globalization.CultureInfo.InvariantCulture, format, args);
            Write(line);
        }


        public override string ToString()
        {
            return builder_.ToString();
        }

        public void SaveToFile(string filePath)
        {
            if(string.IsNullOrEmpty(filePath))
            {
                throw new ArgumentException("File path is null or empty.", nameof(filePath));
            }
            var directory = Path.GetDirectoryName(filePath);
            if (string.IsNullOrEmpty(directory) == false && !Directory.Exists(directory))
            {
                Directory.CreateDirectory(directory);
            }

            var text = builder_.ToString();
            if (File.Exists(filePath))
            {
                var existingText = File.ReadAllText(filePath);
                if (string.Equals(existingText, text))
                {
                    return;
                }
            }
            
            File.WriteAllText(filePath, builder_.ToString());
        }

    }
}
