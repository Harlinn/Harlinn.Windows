using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

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
            ".c", ".cpp", ".cc", ".cxx", ".c++", ".h", ".hpp", ".hh", ".hxx",
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
            ".sql",
            // Inline C/C++
            ".inl",
            // Assembly
            ".asm", ".s",
            // Include files that may be C/C++ or assembly
            ".inc"
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
                { ".inl", ("/*", "*/") },
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
                { ".jl", ("#=", "=#") },
                // Assembly: use single-line prefix comment ";"; represent end as "\n" to indicate line-based
                { ".asm", (";", "\n") },
                { ".s", (";", "\n") }
            };

        private static int Main(string[] args)
        {
            try
            {
                // parse args: support optional --dry-run/-n and optional start directory
                var dryRun = args.Any(a => string.Equals(a, "--dry-run", StringComparison.OrdinalIgnoreCase) || string.Equals(a, "-n", StringComparison.OrdinalIgnoreCase));
                if (args.Any(a => string.Equals(a, "-h", StringComparison.OrdinalIgnoreCase) || string.Equals(a, "--help", StringComparison.OrdinalIgnoreCase)))
                {
                    Console.WriteLine("Usage: Copyright.Tool [--dry-run|-n] [start-directory]");
                    Console.WriteLine("--dry-run, -n: preview changes without writing files");
                    return 0;
                }

                var startDirArg = args.FirstOrDefault(a => !string.Equals(a, "--dry-run", StringComparison.OrdinalIgnoreCase) && !string.Equals(a, "-n", StringComparison.OrdinalIgnoreCase) && !string.Equals(a, "-h", StringComparison.OrdinalIgnoreCase) && !string.Equals(a, "--help", StringComparison.OrdinalIgnoreCase));
                var startDir = !string.IsNullOrWhiteSpace(startDirArg) ? startDirArg : Directory.GetCurrentDirectory();
                var repoRoot = FindRepositoryRoot(startDir) ?? startDir;

                Console.WriteLine($"Repository root: {repoRoot}");
                Console.WriteLine(dryRun ? "Running in dry-run mode. No files will be written." : "Running in write mode. Files will be updated.");

                var files = EnumerateFiles(repoRoot);
                var modifiedFiles = new List<string>();

                foreach (var file in files)
                {
                    if (ProcessFile(file, dryRun))
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
        private static bool ProcessFile(string filePath, bool dryRun)
        {
            var ext = Path.GetExtension(filePath).ToLowerInvariant();

            // Read raw text preserving encoding when possible
            var originalBytes = File.ReadAllBytes(filePath);
            var encoding = DetectEncoding(originalBytes) ?? Encoding.UTF8;
            var text = encoding.GetString(originalBytes);

            // If file is an include that may be assembly or C/C++, try to determine
            if (ext == ".inc")
            {
                ext = DetectLanguageForInc(text);
            }

            if (!CommentStyles.TryGetValue(ext, out var delimiters))
            {
                return false;
            }

            var insertIndex = 0;
            // Preserve shebang for scripts (python)
            if (ext == ".py")
            {
                if (text.StartsWith("#!"))
                {
                    var firstLineEnd = text.IndexOfAny(new[] { '\r', '\n' });
                    if (firstLineEnd >= 0)
                    {
                        // move past the newline characters
                        if (text[firstLineEnd] == '\r')
                        {
                            if (firstLineEnd + 1 < text.Length && text[firstLineEnd + 1] == '\n') insertIndex = firstLineEnd + 2;
                            else insertIndex = firstLineEnd + 1;
                        }
                        else if (text[firstLineEnd] == '\n') insertIndex = firstLineEnd + 1;
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

            if (commentEnd == "\n")
            {
                // single-line prefix comment style (assembly). Collect consecutive comment lines
                var pos = firstNonWs;
                var sbLen = text.Length;
                var endPos = pos;
                var foundAny = false;
                while (pos < sbLen)
                {
                    // skip leading whitespace
                    var lineStart = pos;
                    while (lineStart < sbLen && (text[lineStart] == ' ' || text[lineStart] == '\t')) lineStart++;
                    if (lineStart < sbLen && text.Substring(lineStart).StartsWith(commentStart, StringComparison.Ordinal))
                    {
                        foundAny = true;
                        // move to next line
                        var nextNewline = text.IndexOfAny(new[] { '\r', '\n' }, lineStart);
                        if (nextNewline < 0) { endPos = sbLen; break; }
                        // advance past newline sequence
                        if (text[nextNewline] == '\r' && nextNewline + 1 < sbLen && text[nextNewline + 1] == '\n') pos = nextNewline + 2;
                        else pos = nextNewline + 1;
                        endPos = pos;
                        continue;
                    }
                    break;
                }

                if (foundAny)
                {
                    hasTopComment = true;
                    topCommentRange = (firstNonWs, endPos);
                }
            }
            else
            {
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
            }

            var modified = false;
            var newText = text;

            // Regex to find Espen Harlinn copyright occurrences (any year or range) on a single line
            var espPattern = new Regex(@"Copyright\s+\d{4}(?:-\d{4})?\s+Espen Harlinn", RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);
            var replacement = "Copyright 2024-2026 Espen Harlinn";

            // Find all matches in the file that are outside quoted strings on the same line
            var allMatches = espPattern.Matches(text).Cast<Match>().ToList();
            var espMatches = allMatches.Where(m => IsOutsideQuotedString(text, m.Index, m.Length)).ToList();

            if (espMatches.Count > 0)
            {
                // File already contains Espen somewhere -> update those occurrences and remove duplicates
                newText = espPattern.Replace(text, replacement);
                // Recompute matches in newText and remove duplicates keeping first occurrence
                var newMatches = espPattern.Matches(newText).Cast<Match>().ToList();
                if (newMatches.Count > 1)
                {
                    newText = RemoveOtherEspenOccurrences(newText, newMatches, delimiters);
                }

                if (newText != text)
                {
                    modified = true;
                }
            }
            else
            {
                // No Espen anywhere in the file -> insert header at top (respecting shebang)
                var header = BuildHeaderFor(ext);

                if (hasTopComment)
                {
                    // insert above existing top comment
                    newText = text.Substring(0, firstNonWs) + header + Environment.NewLine + text.Substring(firstNonWs);
                }
                else
                {
                    var insertion = insertIndex >= 0 ? insertIndex : 0;
                    newText = text.Substring(0, insertion) + header + Environment.NewLine + text.Substring(insertion);
                }

                modified = true;

                // After insertion ensure only single Espen occurrence (should be only one)
                var newMatches = espPattern.Matches(newText).Cast<Match>().ToList();
                if (newMatches.Count > 1)
                {
                    newText = RemoveOtherEspenOccurrences(newText, newMatches, delimiters);
                }
            }

            if (modified)
            {
                // Final defensive replace to normalize any remaining patterns
                newText = espPattern.Replace(newText, replacement);

                if (dryRun)
                {
                    PrintPreview(filePath, newText);
                }
                else
                {
                    var newBytes = encoding.GetBytes(newText);
                    File.WriteAllBytes(filePath, newBytes);
                }
            }

            return modified;
        }

        private static bool IsOutsideQuotedString(string text, int matchIndex, int matchLength)
        {
            // Determine the bounds of the line containing the match
            var lineStart = text.LastIndexOfAny(new[] { '\r', '\n' }, matchIndex);
            lineStart = lineStart >= 0 ? lineStart + 1 : 0;
            var lineEnd = text.IndexOfAny(new[] { '\r', '\n' }, matchIndex + matchLength);
            if (lineEnd < 0) lineEnd = text.Length;

            var line = text.Substring(lineStart, lineEnd - lineStart);
            var indexInLine = matchIndex - lineStart;

            // Count quotes before the match on the same line
            int doubleQuotesBefore = 0;
            int singleQuotesBefore = 0;
            for (int i = 0; i < Math.Min(indexInLine, line.Length); i++)
            {
                if (line[i] == '"') doubleQuotesBefore++;
                if (line[i] == '\'') singleQuotesBefore++;
            }

            // If odd number of quotes before the match of either type, it's inside a quoted string
            if ((doubleQuotesBefore % 2) == 1) return false;
            if ((singleQuotesBefore % 2) == 1) return false;
            return true;
        }

        private static void PrintPreview(string filePath, string newText)
        {
            Console.WriteLine();
            Console.WriteLine(filePath);
            var lines = SplitLines(newText);
            var toShow = Math.Min(100, lines.Length);
            for (int i = 0; i < toShow; i++)
            {
                Console.WriteLine("    " + lines[i]);
            }
            if (lines.Length > toShow)
            {
                Console.WriteLine("    ...");
            }
        }

        private static string[] SplitLines(string text)
        {
            return text.Split(new[] { "\r\n", "\n" }, StringSplitOptions.None);
        }

        private static string RemoveOtherEspenOccurrences(string text, List<Match> matches, (string Start, string End) delims)
        {
            // We'll remove all occurrences except the first one (which should be the header or first found occurrence)
            if (matches == null || matches.Count <= 1) return text;

            // Sort matches by index
            var sorted = matches.OrderBy(m => m.Index).ToList();

            // Keep the first occurrence
            var toRemove = sorted.Skip(1).ToList();

            var sb = new StringBuilder(text);
            // We will remove ranges from end to start to keep indices stable
            var removalRanges = new List<(int Start, int End)>();

            foreach (var m in toRemove)
            {
                var idx = m.Index;

                if (delims.End == "\n")
                {
                    // single-line comments: remove contiguous comment lines that contain the match
                    var s = sb.ToString();
                    // find line start
                    var lineStart = s.LastIndexOfAny(new[] { '\r', '\n' }, idx);
                    lineStart = lineStart >= 0 ? lineStart + 1 : 0;
                    // expand upwards to include previous comment lines
                    var start = lineStart;
                    while (start > 0)
                    {
                        var prevLineEnd = start - 1;
                        var prevLineStart = s.LastIndexOfAny(new[] { '\r', '\n' }, prevLineEnd);
                        prevLineStart = prevLineStart >= 0 ? prevLineStart + 1 : 0;
                        var trimmed = s.Substring(prevLineStart).TrimStart();
                        if (trimmed.StartsWith(delims.Start, StringComparison.Ordinal))
                        {
                            start = prevLineStart;
                            continue;
                        }
                        break;
                    }

                    // find line end and expand downwards to include following comment lines
                    var end = s.IndexOfAny(new[] { '\r', '\n' }, idx + m.Length);
                    if (end < 0) end = s.Length;
                    var next = end;
                    while (next < s.Length)
                    {
                        var nextLineStart = next;
                        while (nextLineStart < s.Length && (s[nextLineStart] == '\r' || s[nextLineStart] == '\n')) nextLineStart++;
                        if (nextLineStart >= s.Length) break;
                        var trimmed = s.Substring(nextLineStart).TrimStart();
                        if (trimmed.StartsWith(delims.Start, StringComparison.Ordinal))
                        {
                            var nextLineEnd = s.IndexOfAny(new[] { '\r', '\n' }, nextLineStart);
                            if (nextLineEnd < 0) nextLineEnd = s.Length;
                            next = nextLineEnd;
                            end = next;
                            continue;
                        }
                        break;
                    }

                    removalRanges.Add((start, end));
                }
                else
                {
                    // Try to remove entire comment block containing the match
                    var s = sb.ToString();
                    var startIdx = s.LastIndexOf(delims.Start, idx, StringComparison.Ordinal);
                    var endIdx = s.IndexOf(delims.End, idx + m.Length, StringComparison.Ordinal);

                    if (startIdx >= 0 && endIdx > startIdx)
                    {
                        removalRanges.Add((startIdx, endIdx + delims.End.Length));
                    }
                    else
                    {
                        // Remove the full line containing the match
                        var lineStart = s.LastIndexOfAny(new[] { '\r', '\n' }, idx);
                        lineStart = lineStart >= 0 ? lineStart + 1 : 0;
                        var lineEnd = s.IndexOfAny(new[] { '\r', '\n' }, idx + m.Length);
                        if (lineEnd < 0) lineEnd = s.Length;
                        removalRanges.Add((lineStart, lineEnd));
                    }
                }
            }

            // Merge overlapping ranges and remove from end
            var merged = MergeRanges(removalRanges);
            for (int i = merged.Count - 1; i >= 0; i--)
            {
                sb.Remove(merged[i].Start, merged[i].End - merged[i].Start);
            }

            return sb.ToString();
        }

        private static List<(int Start, int End)> MergeRanges(List<(int Start, int End)> ranges)
        {
            var list = ranges.OrderBy(r => r.Start).ToList();
            var merged = new List<(int Start, int End)>();
            foreach (var r in list)
            {
                if (merged.Count == 0) { merged.Add(r); continue; }
                var last = merged[merged.Count - 1];
                if (r.Start <= last.End)
                {
                    // overlap
                    merged[merged.Count - 1] = (last.Start, Math.Max(last.End, r.End));
                }
                else
                {
                    merged.Add(r);
                }
            }
            return merged;
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

            // Single-line prefix comment style (assembly) - delims.End == "\n"
            if (delims.End == "\n")
            {
                foreach (var line in LicenseInner.Split(new[] { "\n" }, StringSplitOptions.None))
                {
                    sb.Append(delims.Start).Append(' ').Append(line).AppendLine();
                }
                // trim trailing newline
                return sb.ToString().TrimEnd('\r', '\n');
            }

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

        /// <summary>
        /// Heuristic to determine whether a .inc file likely contains assembly or C/C++
        /// Defaults to C/C++ when uncertain.
        /// </summary>
        private static string DetectLanguageForInc(string text)
        {
            // Search first part of file for hints
            var sample = text.Length > 2000 ? text.Substring(0, 2000) : text;
            var lower = sample.ToLowerInvariant();

            // Common C/C++ markers
            if (lower.Contains("#include") || lower.Contains("#ifdef") || lower.Contains("#ifndef") ||
                lower.Contains("printf(") || lower.Contains("std::") || lower.Contains("using std") ||
                lower.Contains("int main") || lower.Contains("template<") || lower.Contains("cout<<") ||
                lower.Contains("class ") || lower.Contains("struct ") || lower.Contains("typedef ") ||
                lower.Contains("{" ) || lower.Contains(";\n"))
            {
                return ".c"; // treat as C/C++ for comment style
            }

            // Assembly markers: lines starting with ';' or instructions or directives
            var asmIndicators = new[] { ".section", "section", "bits ", "org ", "db ", "dw ", "dd ", "mov ", "jmp ", "call ", "ret", ":\n", "\n\t" };
            foreach (var ind in asmIndicators)
            {
                if (lower.Contains(ind)) return ".asm";
            }

            // If file has many lines that start with alphanumeric label plus ':' it's likely assembly
            var lines = sample.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            var labelCount = lines.Count(l => Regex.IsMatch(l, "^\\s*[a-zA-Z0-9_]+:\\s*(;.*)?$") );
            if (labelCount > 1) return ".asm";

            // Default to C/C++
            return ".c";
        }
    }
}
