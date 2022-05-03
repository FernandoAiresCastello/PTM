using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTMC
{
    public class Compiler
    {
        public bool Success { get; private set; } = false;

        public void Run(string ptmlSourceFile, string transpiledSourceFile)
        {
            if (!File.Exists(transpiledSourceFile))
            {
                Console.WriteLine("Transpiled C file not found: " + transpiledSourceFile);
                return;
            }

            string outputFolder = Environment.CurrentDirectory;
            string outputExeFileName = Path.GetFileNameWithoutExtension(ptmlSourceFile) + ".exe";
            string outputExePath = Path.Combine(outputFolder, outputExeFileName);
            string ptmApiSourceFiles = "ptm.c";

            var psi = new ProcessStartInfo(Environment.CurrentDirectory + "\\mingw\\bin\\gcc");
            psi.UseShellExecute = false;
            psi.EnvironmentVariables["PATH"] = Environment.CurrentDirectory + "\\mingw\\bin";
            psi.Arguments = $"-static-libgcc {ptmApiSourceFiles} {transpiledSourceFile} -o \"{outputExePath}\" -lmingw32 -lSDL2main -lSDL2 -mwindows";
            Process.Start(psi);

            string sdlFilePath = Path.Combine(outputFolder, "SDL2.dll");
            if (!File.Exists(sdlFilePath))
                File.Copy("SDL2.dll", sdlFilePath);

            Success = true;
        }
    }
}
