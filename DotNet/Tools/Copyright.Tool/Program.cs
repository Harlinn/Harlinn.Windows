using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Copyright.Tool
{
    /// <summary>
    /// Small console tool that ensures all source files in a repository contain
    /// the project copyright/license header. It updates existing Espen Harlinn
    /// copyright years and inserts the header where missing.
    /// </summary>
    internal static class Program
    {
        private static readonly string[] IgnoreDirectories = new[]
        {
            ".cr", ".git", ".github", ".vs", "3rdParty", "packages", "x64"
        };

        // Extensions to process (lowercase)
        private static readonly string[] AllowedExtensions = new[]
        {
            // C/C++
            ".c", ".cpp", ".cc", ".cxx", ".h", ".hpp", ".hh", ".hxx",
            // C#
            ".cs",
            // Java
            ".java",
            // Julia
            ".jl",
            // Rust
            ".rs",
            // JavaScript
            ".js", ".jsx", ".mjs",
            // Python
            ".py",
            // SQL (PL/SQL and T/SQL)
            ".sql"
        };

        // The canonical license text inner body with updated years 2024-2026
        private const string LicenseInner =
"   Copyright 2024-2026 Espen Harlinn\n\n   Licensed under the Apache License, Version 2.0 (the \"License\");\n   you may not use this file except in compliance with the License.\n   You may obtain a copy of the License at\n\n       http://www.apache.org/licenses/LICENSE-2.0\n\n   Unless required by applicable law or agreed to in writing, software\n   distributed under the License is distributed on an \"AS IS\" BASIS,\n   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n   See the License for the specific language governing permissions and\n   limitations under the License.";

        private static readonly Dictionary<string, (string Start, string End)> CommentStyles =
            new(StringComparer.OrdinalIgnoreCase)
            {
                // Block comment style
                // Extensions mapped to block style (/* */)
                { ".c", ("/*", "*/") },
                { ".cpp", ("/*", "*/") },
                { ".cc", ("/*", "*/") },
                { ".cxx", ("/*", "*/") },
                { ".h", ("/*", "*/") },
                { ".hpp", ("/*", "*/") },
                { ".hh", ("/*", "*/") },
                { ".hxx", ("/*", "*/") },
                { ".cs", ("/*", "*/") },
                { ".java", ("/*", "*/") },
                { ".js", ("/*", "*/") },
                { ".jsx", ("/*", "*/") },
                { ".mjs", ("/*", "*/") },
                { ".rs", ("/*", "*/") },
                { ".sql", ("/*", "*/") },
                // Python uses triple double-quotes for multiline comment-like literal
                { ".py", ("\"\"\"", "\"\"\"") },
                // Julia block comment
                { ".jl", ("#=", "=#") }
            };

        private static int Main(string[] args)
        {
            try
            {
                var startDir = args.Length > 0 ? args[0] : Directory.GetCurrentDirectory();
                var repoRoot = FindRepositoryRoot(startDir) ?? startDir;

                Console.WriteLine($"Repository root: {repoRoot}");

                var files = EnumerateFiles(repoRoot);
                var modifiedFiles = new List<string>();

                foreach (var file in files)
                {
                    if (ProcessFile(file))
                    {
                        modifiedFiles.Add(file);
                    }
                }

                Console.WriteLine($"Processed {files.Count} files. Modified {modifiedFiles.Count} files.");
                foreach (var f in modifiedFiles)
                {
                    Console.WriteLine($"Updated: {f}");
                }

                return 0;
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"Error: {ex.Message}");
                return 1;
            }
        }

        /// <summary>
        /// Find repository root by walking up and locating a ".git" directory.
        /// If not found, returns null.
        /// </summary>
        private static string? FindRepositoryRoot(string startDir)
        {
            var dir = new DirectoryInfo(startDir);
            while (dir != null)
            {
                var git = Path.Combine(dir.FullName, ".git");
                if (Directory.Exists(git) || File.Exists(git))
                {
                    return dir.FullName;
                }
                dir = dir.Parent;
            }
            return null;
        }

        /// <summary>
        /// Enumerates allowed files under root excluding ignored directories.
        /// </summary>
        private static List<string> EnumerateFiles(string root)
        {
            var results = new List<string>();
            var stack = new Stack<string>();
            stack.Push(root);

            while (stack.Count > 0)
            {
                var dir = stack.Pop();
                try
                {
                    var dirName = Path.GetFileName(dir)?.ToLowerInvariant() ?? string.Empty;
                    if (IgnoreDirectories.Any(ignore => string.Equals(ignore, dirName, StringComparison.OrdinalIgnoreCase)))
                    {
                        continue;
                    }

                    foreach (var sub in Directory.GetDirectories(dir))
                    {
                        var subName = Path.GetFileName(sub) ?? string.Empty;
                        if (IgnoreDirectories.Any(ignore => string.Equals(ignore, subName, StringComparison.OrdinalIgnoreCase)))
                        {
                            continue;
                        }
                        stack.Push(sub);
                    }

                    foreach (var file in Directory.GetFiles(dir))
                    {
                        var ext = Path.GetExtension(file).ToLowerInvariant();
                        if (AllowedExtensions.Contains(ext))
                        {
                            results.Add(file);
                        }
                    }
                }
                catch (UnauthorizedAccessException)
                {
                    // ignore folders we cannot access
                }
            }

            return results;
        }

        /// <summary>
        /// Process a single file: update existing Espen Harlinn years or insert header when missing.
        /// Returns true when file was modified.
        /// </summary>
        private static bool ProcessFile(string filePath)
        {
            var ext = Path.GetExtension(filePath).ToLowerInvariant();
            if (!CommentStyles.TryGetValue(ext, out var delimiters))
            {
                return false;
            }

            // Read raw text preserving encoding when possible
            var originalBytes = File.ReadAllBytes(filePath);
            var encoding = DetectEncoding(originalBytes) ?? Encoding.UTF8;
            var text = encoding.GetString(originalBytes);

            var insertIndex = 0;
            // Preserve shebang for scripts (python)
            if (ext == ".py")
            {
                if (text.StartsWith("#!"))
                {
                    var firstLineEnd = text.IndexOfAny(new[] { '\r', '\n' });
                    if (firstLineEnd >= 0)
                    {
                        insertIndex = firstLineEnd;
                        // move past the newline characters
                        if (text.Length > firstLineEnd && text[firstLineEnd] == '\r')
                        {
                            if (firstLineEnd + 1 < text.Length && text[firstLineEnd + 1] == '\n') insertIndex = firstLineEnd + 2;
                            else insertIndex = firstLineEnd + 1;
                        }
                        else if (text.Length > firstLineEnd && text[firstLineEnd] == '\n') insertIndex = firstLineEnd + 1;
                    }
                }
            }

            // Find first non-whitespace after insertIndex
            var firstNonWs = FindFirstNonWhiteSpaceIndex(text, insertIndex);
            if (firstNonWs < 0) firstNonWs = text.Length;

            // If file starts with a comment block at or after insertIndex, detect it
            var hasTopComment = false;
            var commentStart = delimiters.Start;
            var commentEnd = delimiters.End;
            var topCommentRange = (Start: -1, End: -1);

            if (firstNonWs + commentStart.Length <= text.Length &&
                text.Substring(firstNonWs, Math.Min(commentStart.Length, text.Length - firstNonWs)) == commentStart)
            {
                // parse until commentEnd
                var searchStart = firstNonWs + commentStart.Length;
                var endIndex = text.IndexOf(commentEnd, searchStart, StringComparison.Ordinal);
                if (endIndex >= 0)
                {
                    topCommentRange = (firstNonWs, endIndex + commentEnd.Length);
                    hasTopComment = true;
                }
            }

            var modified = false;
            var newText = text;

            if (hasTopComment)
            {
                var existingComment = text.Substring(topCommentRange.Start, topCommentRange.End - topCommentRange.Start);
                if (existingComment.Contains("Espen Harlinn", StringComparison.OrdinalIgnoreCase))
                {
                    // Replace outdated year patterns
                    var updatedComment = existingComment
                        .Replace("Copyright 2024 Espen Harlinn", "Copyright 2024-2026 Espen Harlinn")
                        .Replace("Copyright 2024-2025 Espen Harlinn", "Copyright 2024-2026 Espen Harlinn");

                    if (updatedComment != existingComment)
                    {
                        newText = text.Substring(0, topCommentRange.Start) + updatedComment + text.Substring(topCommentRange.End);
                        modified = true;
                    }
                    // If Espen present but no update needed, leave as-is
                }
                else
                {
                    // Top comment exists but not Espen header - insert our header above it
                    var header = BuildHeaderFor(ext);
                    newText = text.Substring(0, firstNonWs) + header + Environment.NewLine + text.Substring(firstNonWs);
                    modified = true;
                }
            }
            else
            {
                // No top comment - insert our header at insertIndex or firstNonWs
                var header = BuildHeaderFor(ext);
                var insertion = insertIndex >= 0 ? insertIndex : 0;
                // if insertIndex is in middle of whitespace, find first newline after insertIndex to keep leading whitespace intact
                newText = text.Substring(0, insertion) + header + Environment.NewLine + text.Substring(insertion);
                modified = true;
            }

            if (modified)
            {
                // Before writing, normalize any older Espen patterns elsewhere in file too
                newText = newText
                    .Replace("Copyright 2024 Espen Harlinn", "Copyright 2024-2026 Espen Harlinn")
                    .Replace("Copyright 2024-2025 Espen Harlinn", "Copyright 2024-2026 Espen Harlinn");

                var newBytes = encoding.GetBytes(newText);
                File.WriteAllBytes(filePath, newBytes);
            }

            return modified;
        }

        /// <summary>
        /// Build the header text wrapped in the appropriate comment delimiters
        /// for a given file extension.
        /// </summary>
        private static string BuildHeaderFor(string extension)
        {
            if (!CommentStyles.TryGetValue(extension, out var delims))
            {
                delims = ("/*", "*/");
            }

            var sb = new StringBuilder();

            // For block comment styles like /* ... */ put the inner text on separate lines
            if (delims.Start == "/*" && delims.End == "*/")
            {
                sb.Append(delims.Start).AppendLine();
                foreach (var line in LicenseInner.Split(new[] { "\n" }, StringSplitOptions.None))
                {
                    sb.Append(' ').Append(line).AppendLine();
                }
                sb.Append(delims.End);
                return sb.ToString();
            }

            // Python triple-quote
            if (delims.Start == "\"\"\"" && delims.End == "\"\"\"")
            {
                sb.Append(delims.Start).AppendLine();
                sb.Append(LicenseInner.Replace("\\n", Environment.NewLine)).AppendLine();
                sb.Append(delims.End);
                return sb.ToString();
            }

            // Julia style #= =#
            if (delims.Start == "#=" && delims.End == "=#")
            {
                sb.Append(delims.Start).AppendLine();
                foreach (var line in LicenseInner.Split(new[] { "\\n" }, StringSplitOptions.None))
                {
                    sb.Append(' ').Append(line).AppendLine();
                }
                sb.Append(delims.End);
                return sb.ToString();
            }

            // Fallback to simple block comment
            sb.Append("/*").AppendLine();
            foreach (var line in LicenseInner.Split(new[] { "\\n" }, StringSplitOptions.None))
            {
                sb.Append(' ').Append(line).AppendLine();
            }
            sb.Append("*/");
            return sb.ToString();
        }

        /// <summary>
        /// Find index of first non-whitespace char after a start position.
        /// </summary>
        private static int FindFirstNonWhiteSpaceIndex(string text, int start)
        {
            for (var i = start; i < text.Length; i++)
            {
                if (!char.IsWhiteSpace(text[i])) return i;
            }
            return -1;
        }

        /// <summary>
        /// Attempt to detect encoding using BOM. Returns null when unknown.
        /// </summary>
        private static Encoding? DetectEncoding(byte[] bytes)
        {
            if (bytes.Length >= 3 && bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF)
                return new UTF8Encoding(true);
            if (bytes.Length >= 2 && bytes[0] == 0xFE && bytes[1] == 0xFF)
                return Encoding.BigEndianUnicode;
            if (bytes.Length >= 2 && bytes[0] == 0xFF && bytes[1] == 0xFE)
                return Encoding.Unicode;
            if (bytes.Length >= 4 && bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0xFE && bytes[3] == 0xFF)
                return Encoding.GetEncoding("utf-32BE");
            if (bytes.Length >= 4 && bytes[0] == 0xFF && bytes[1] == 0xFE && bytes[2] == 0x00 && bytes[3] == 0x00)
                return Encoding.UTF32;
            return null;
        }
    }
}
