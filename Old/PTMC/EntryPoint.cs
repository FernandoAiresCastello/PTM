using System;
using System.IO;

namespace PTMC
{
    public class EntryPoint
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("PTMC - Programmable Tile Machine Compiler");

            const string ptmlSourceFile = "test.ptml";
            const string transpiledSourceFile = "generated.c";

            if (!File.Exists(ptmlSourceFile))
            {
                Console.WriteLine($"Source file not found: {ptmlSourceFile}");
                return;
            }

            Console.WriteLine("Compiling PTML to C...");
            var transpiler = new Transpiler();
            transpiler.Run(ptmlSourceFile, transpiledSourceFile);
            
            if (transpiler.Success)
            {
                Console.WriteLine("Compiling C to EXE...");
                var compiler = new Compiler();
                compiler.Run(ptmlSourceFile, transpiledSourceFile);

                if (compiler.Success)
                {
                    Console.WriteLine("Success!");
                }
            }
        }
    }
}
