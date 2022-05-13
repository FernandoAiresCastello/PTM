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
            c.AppendLine("ptm_init();");

            var ptml = File.ReadAllLines(ptmlSourceFile);
            int srcLineNumber = 1;

            foreach (var ptmlLine in ptml)
            {
                string trimmedLine = ptmlLine.Trim();

                if (trimmedLine != string.Empty)
                {
                    if (trimmedLine.StartsWith(";"))
                    {
                        c.AppendLine("//" + trimmedLine.Substring(1));
                    }
                    else
                    {
                        var transpiledLine = TranspileLine(trimmedLine, srcLineNumber);
                        if (transpiledLine != null)
                            c.AppendLine(transpiledLine);
                        else
                            return;
                    }
                }
                else
                {
                    c.AppendLine(trimmedLine);
                }

                srcLineNumber++;
            }

            c.AppendLine("ptm_exit();");
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
            string args;

            if (indexOfFirstSpace > 0)
            {
                cmd = ptml.Substring(0, indexOfFirstSpace).ToUpper();
                args = ptml.Substring(indexOfFirstSpace).Trim();
            }
            else
            {
                cmd = ptml.ToUpper();
                args = "";
            }

            if (cmd == "WINDOW")
            {
                return $"ptm_open_window({args});";
            }
            else if (cmd == "HALT")
            {
                return $"ptm_halt();";
            }
            else if (cmd == "EXIT")
            {
                return $"ptm_exit();";
            }
            else if (cmd == "LPSET")
            {
                return $"ptm_put_pixel_linear({args});";
            }
            else if (cmd == "PSET")
            {
                return $"ptm_put_pixel({args});";
            }
            else if (cmd == "REFR")
            {
                return $"ptm_update_window();";
            }
            else if (cmd == "CLS")
            {
                return $"ptm_clear_window({args});";
            }
            else if (cmd == "FOR")
            {

            }
            else
            {
                Error("Unknown command", ptml, srcLineNumber);
            }

            return null;
        }
    }
}
