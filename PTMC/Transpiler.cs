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

        public void Run(string ptmlSourceFile, string transpiledSourceFile)
        {
            StringBuilder c = new StringBuilder();
            c.AppendLine("#include \"ptm.h\"");
            c.AppendLine("int main(int argc, char* argv[]) {");

            var ptml = File.ReadAllLines(ptmlSourceFile);
            int srcLineNumber = 1;

            foreach (var ptmlLine in ptml)
            {
                if (ptmlLine.Trim() != string.Empty)
                {
                    var transpiledLine = TranspileLine(ptmlLine, srcLineNumber);
                    if (transpiledLine != null)
                        c.AppendLine(transpiledLine);
                    else
                        return;
                }
                else
                {
                    c.AppendLine(ptmlLine);
                }

                srcLineNumber++;
            }

            c.AppendLine("return 0; }");

            File.WriteAllText(transpiledSourceFile, c.ToString());
            Success = true;
        }

        private void Error(string msg, string srcLine, int srcLineNumber)
        {
            Console.WriteLine($"ERROR at line {srcLineNumber}: " + msg);
            Console.WriteLine($"Source: {srcLine}");
        }

        private string TranspileLine(string ptml, int srcLineNumber)
        {
            string cmd;
            ptml = ptml.Trim();
            int indexOfFirstSpace = ptml.IndexOf(' ');

            if (indexOfFirstSpace > 0)
                cmd = ptml.Substring(0, indexOfFirstSpace).ToUpper();
            else
                cmd = ptml.ToUpper();

            if (cmd == "TEST")
            {
                return "test();";
            }
            else
            {
                Error("Unknown command", ptml, srcLineNumber);
            }

            return null;
        }
    }
}
