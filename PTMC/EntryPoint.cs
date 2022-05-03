using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTMC
{
    public class EntryPoint
    {
        public static void Main(string[] args)
        {
            string ptmlSourceFile = "test.ptml";

            var transpiler = new Transpiler();
            transpiler.Run(ptmlSourceFile);

            var compiler = new Compiler();
            compiler.Run(ptmlSourceFile);
        }
    }
}
