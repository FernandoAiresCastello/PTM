using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTMC
{
    public class Transpiler
    {
        public bool Success { get; private set; } = false;

        public void Run(string ptmlSourceFile)
        {
            var file = File.ReadAllLines(ptmlSourceFile);

            foreach (var line in file)
            {
            }
        }
    }
}
