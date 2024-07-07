using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTMStudio
{
    public class Filesystem
    {
        public static readonly string AbsoluteRootPath = NormalizePath(Environment.CurrentDirectory);
        public static readonly string AbsoluteRootFilesPath = NormalizePath(Path.Combine(AbsoluteRootPath, "files"));

        public static string NormalizePath(string path)
        {
            return path.Replace("\\", "/");
        }

        public static string RemoveAbsoluteRoot(string path)
        {
            return path.Replace(AbsoluteRootPath, "");
        }

        public static string RemoveAbsoluteRootAndFilesPrefix(string path)
        {
            return RemoveFilesPrefix(path.Replace(AbsoluteRootPath, ""));
        }

        public static string RemoveFilesPrefix(string path)
        {
            if (path.StartsWith("/files/"))
                path = path.Substring(7);
            else if (path.StartsWith("files/"))
                path = path.Substring(6);

            return path;
        }
    }
}
