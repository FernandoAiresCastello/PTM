using PTMStudio.Core;
using System;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio
{
	public static class Filesystem
    {
		public const string SysRootDirName = "SYS";
		public const string UserRootDirName = "USR";
		public const string ProjectDirName = "PROJ";

		public static readonly string CurrentDir = NormalizePath(Environment.CurrentDirectory);
        public static readonly string UserRoot = NormalizePath(Path.Combine(Environment.CurrentDirectory, UserRootDirName));
        public static readonly string SysRoot = NormalizePath(Path.Combine(Environment.CurrentDirectory, SysRootDirName));

		public const string ScratchpadProjectFolder = "SCRATCHPAD";
		public const string DefaultMainProgramFileName = "MAIN" + KnownFileExtensions.Program;
		public static readonly string DefaultPaletteFile = GetSystemFilePath("DEFAULT.PAL");
        public static readonly string DefaultTilesetFile = GetSystemFilePath("DEFAULT.CHR");

		public static readonly string[] SpecialFiles =
        {
			"AUTOEXEC.PTM", "AUTOSAVE.PTM", "TEMP.PTM"
		};

        public static string NormalizePath(string path)
        {
            return path.Replace("\\", "/");
        }

        public static string RemoveAbsoluteRoot(string path)
        {
            return path.Replace(CurrentDir, "");
        }

		public static string RemoveAbsoluteRootAndNormalizePath(string path)
        {
            return NormalizePath(RemoveAbsoluteRoot(path));
        }

		public static string RemoveAbsoluteRootAndFilesPrefix(string path)
        {
            return RemoveFilesPrefix(path.Replace(CurrentDir, ""));
        }

        public static string RemoveFilesPrefix(string path)
        {
            return new FileInfo(path).Name;
        }

		public static string GetUserFilePath(string file)
        {
			return Path.Combine(UserRoot, file);
		}

		public static string GetSystemFilePath(string file)
        {
            return Path.Combine(SysRoot, file);
        }

        public static string GetAbsoluteUserFilePath(string file)
        {
            string appRoot = Path.GetDirectoryName(Application.ExecutablePath);
            return Path.Combine(appRoot, GetUserFilePath(file));
        }
    }
}
