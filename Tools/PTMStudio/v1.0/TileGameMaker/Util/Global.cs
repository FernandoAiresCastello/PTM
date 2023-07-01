using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TileGameMaker.Util
{
    public static class Global
    {
        public static string ProgramTitle => "PTM Studio";
        public static Icon WindowIcon => Icon.FromHandle(Properties.Resources.ptm_icon_2_fw.GetHicon());
    }
}
