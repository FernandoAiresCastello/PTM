using System;
using System.IO;

namespace PTMStudio
{
    public static class Filesystem
    {
        private static readonly string RootDir = "ROOT";
        private static readonly string SysDir = "SYS";

        public static readonly string CurrentDir = NormalizePath(Environment.CurrentDirectory);
        public static readonly string Root = NormalizePath(Path.Combine(Environment.CurrentDirectory, RootDir));
        public static readonly string SysRoot = NormalizePath(Path.Combine(Environment.CurrentDirectory, SysDir));

        public static readonly string DefaultPaletteFile = GetSystemFilePath("DEFAULT.PAL");
        public static readonly string DefaultTilesetFile = GetSystemFilePath("DEFAULT.CHR");

        public static string NormalizePath(string path)
        {
            return path.Replace("\\", "/");
        }

        public static string RemoveAbsoluteRoot(string path)
        {
            return path.Replace(CurrentDir, "");
        }

        public static string RemoveAbsoluteRootAndFilesPrefix(string path)
        {
            return RemoveFilesPrefix(path.Replace(CurrentDir, ""));
        }

        public static string RemoveFilesPrefix(string path)
        {
            if (path.StartsWith($"/{RootDir}/") || path.StartsWith($"/{SysDir}/"))
                path = path.Substring(7);
            else if (path.StartsWith($"{RootDir}/") || path.StartsWith($"{SysDir}/"))
                path = path.Substring(6);

            return path;
        }

        public static string GetSystemFilePath(string file)
        {
            return Path.Combine(SysRoot, file);
        }
    }
}
