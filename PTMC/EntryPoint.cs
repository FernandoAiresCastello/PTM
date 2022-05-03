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
            var file = File.ReadAllLines("test.ptml");

            foreach (var line in file)
            {
            }
        }
    }
}
