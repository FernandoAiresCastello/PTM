#include <fstream>
#include <filesystem>
#include "PTM.h"
#include "t_filesystem.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_interpreter.h"
#include "t_record_file.h"
#include "t_screen.h"

t_string directory = "";
const t_string root_directory = "ROOT";
const t_string palette_ext = ".PAL";
const t_string charset_ext = ".CHR";
const t_string screen_ext = ".SCR";

#define CRLF        "\r\n"
#define ROOT        "root\\"
#define PATH(x)     (ROOT + directory.trim().to_upper().s_str() + "\\" + x.trim().to_upper().s_str())
#define ROOTPATH(x) (ROOT + x.trim().to_upper().s_str())

constexpr int bytes_per_line = 16;

namespace fs = std::filesystem;

t_list<t_string> t_filesystem::illegal_filenames = {
    root_directory, "CON", "PRN", "AUX", "NUL",
    "COM0", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "COM¹", "COM²", "COM³", 
    "LPT0", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9", "LPT¹", "LPT²", "LPT³"
};

t_record_file record_file;

bool t_filesystem::is_valid_filename(const t_string& filename)
{
    t_string trimmed_filename = filename.trim().to_upper();

    if (trimmed_filename.empty())
        return false;
    if (trimmed_filename == "." || trimmed_filename == "..")
        return false;
    if (trimmed_filename.contains("."))
        return false;
    if (trimmed_filename.in(illegal_filenames))
        return false;
    if (filename.contains_any(" <>:\"/\\|?*"))
        return false;

    return true;
}

bool t_filesystem::file_exists(const t_string& filename)
{
    if (!is_valid_filename(filename))
        return false;

    return 
        fs::exists(fs::path(PATH(filename))) && 
        fs::is_regular_file(fs::path(PATH(filename)));
}

bool t_filesystem::directory_exists(const t_string& name)
{
    if (!is_valid_filename(name))
        return false;

    return 
        fs::exists(fs::path(ROOTPATH(name))) && 
        fs::is_directory(fs::path(ROOTPATH(name)));
}

t_list<t_string> t_filesystem::list_files(const char* prefix)
{
    t_list<t_string> files;

    for (const auto& entry : fs::directory_iterator(ROOT + directory.s_str())) {
        if (fs::is_directory(entry.status())) {
            const auto&& path = entry.path().filename().string();
            if (path.contains('.'))
                continue;
            const auto&& dir = path + "/";
            if (prefix) {
                if (path.starts_with(prefix))
                    files.emplace_back(dir);
            }
            else {
                files.emplace_back(dir);
            }
        }
    }

    for (const auto& entry : fs::directory_iterator(ROOT + directory.s_str())) {
        if (fs::is_regular_file(entry.status())) {
            const auto&& path = entry.path().filename().string();
            if (path.contains('.'))
                continue;
            if (prefix) {
                if (path.starts_with(prefix))
                    files.emplace_back(path);
            }
            else {
                files.emplace_back(path);
            }
        }
    }

    return files;
}

t_list<t_string> t_filesystem::find_files(const t_string& namepart)
{
    return list_files(namepart.to_upper().c_str());
}

void t_filesystem::write_hex_file(const t_string& data, const t_string& filename)
{
    t_string line;
    t_list<t_string> lines;
    int byte_count = 3;

    line += t_string::fmt("%02X %02X %02X ", 'P', 'T', 'M');

    for (const unsigned char& ch : data.s_str()) {
        line += t_string::fmt("%02X", ch);
        byte_count++;
        if (byte_count < bytes_per_line) {
            line += " ";
        }
        else {
            lines.push_back(line);
            line = "";
            byte_count = 0;
        }
    }
    
    if (!line.empty())
        lines.push_back(line);

    write_all_lines(lines, filename);
}

t_string t_filesystem::read_hex_file(const t_string& filename)
{
    t_string text;
    auto&& byte_lines = read_all_lines(filename);

    for (const auto& line : byte_lines) {
        const auto&& bytes_str = line.split(' ');
        for (const auto& byte_str : bytes_str) {
            unsigned char ch = 0;
            try {
                ch = std::stoi(byte_str.s_str(), nullptr, 16);
            }
            catch (std::exception) {
                return "";
            }
            text += ch;
        }
    }

    if (text.length() >= 3 && text[0] == 'P' && text[1] == 'T' && text[2] == 'M') {
        text = text.skip(3);
        return text;
    }
    
    return "";
}

t_string t_filesystem::read_all_text(const t_string& filename)
{
    std::ifstream file(PATH(filename), std::ios::in | std::ios::binary | std::ios::ate);
    if (!file)
        throw std::runtime_error("Could not open file");

    std::ifstream::pos_type fileSize = file.tellg();
    std::string content(fileSize, '\0');

    file.seekg(0, std::ios::beg);
    file.read(&content[0], fileSize);

    return content;
}

t_list<t_string> t_filesystem::read_all_lines(const t_string& filename)
{
    t_list<t_string> lines;
    t_string&& contents = read_all_text(filename);
    auto raw_lines = contents.split('\n');

    for (auto& line : raw_lines)
        lines.push_back(line.replace("\r", ""));

    return lines;
}

void t_filesystem::write_all_text(const t_string& text, const t_string& filename)
{
    std::ofstream file(PATH(filename), std::ios::out | std::ios::binary);
    if (!file)
        throw std::runtime_error("Could not open file");

    file.write(text.s_str().data(), text.s_str().size());
}

void t_filesystem::write_all_lines(const t_list<t_string>& lines, const t_string& filename)
{
    t_string text;

    for (auto& line : lines) {
        text += line;
        text += CRLF;
    }

    write_all_text(text, filename);
}

bool t_filesystem::rename_file(const t_string& old_name, const t_string& new_name)
{
    try
    {
        fs::rename(PATH(old_name), PATH(new_name));
        return true;
    }
    catch (std::exception)
    {
        return false;
    }
}

bool t_filesystem::delete_file(const t_string& name)
{
    try
    {
        fs::remove(PATH(name));
        return true;
    }
    catch (std::exception)
    {
        return false;
    }
}

bool t_filesystem::rename_directory(const t_string& old_name, const t_string& new_name)
{
    try
    {
        fs::rename(ROOTPATH(old_name), ROOTPATH(new_name));
        return true;
    }
    catch (std::exception)
    {
        return false;
    }
}

bool t_filesystem::delete_directory(const t_string& name)
{
    try
    {
        fs::remove_all(ROOTPATH(name));
        return true;
    }
    catch (std::exception)
    {
        return false;
    }
}

void t_filesystem::save_program_plaintext(t_program* prg, const t_string& filename)
{
    write_all_text(prg->get_full_source_text(), filename);
}

void t_filesystem::load_program_plaintext(t_interpreter* intp, t_program* prg, const t_string& filename)
{
    auto src_lines = read_all_lines(filename);

    prg->lines.clear();

    int line_nr = 0;

    for (auto& src_line : src_lines) {
        if (src_line.trim().empty())
            continue;

        line_nr += 10;
        auto&& line = t_string::from_int(line_nr) + " " + src_line;
        intp->interpret_line(line, true);
        if (!intp->get_last_error().empty()) {
            prg->lines.clear();
            break;
        }
    }
}

void t_filesystem::create_directory(const t_string& dir)
{
    fs::create_directory(ROOTPATH(dir));
}

void t_filesystem::change_directory(const t_string& dir)
{
    if (dir == root_directory)
        directory = "";
    else
        directory = dir.to_upper();
}

const t_string& t_filesystem::get_current_directory()
{
    return directory.empty() ? root_directory : directory;
}

const t_string& t_filesystem::get_root_directory()
{
    return root_directory;
}

void t_filesystem::save_charset_plaintext(t_charset* chr, const t_string& filename)
{
    t_list<t_string> chr_entries;
    for (int i = 0; i < chr->size(); i++) {
        t_binary& entry = chr->get(i);
        chr_entries.push_back(entry);
    }
    write_all_lines(chr_entries, filename + charset_ext);
}

void t_filesystem::save_palette_plaintext(t_palette* pal, const t_string& filename)
{
    t_list<t_string> pal_entries;
    for (int i = 0; i < pal->size(); i++) {
        t_color& entry = pal->get(i);
        pal_entries.push_back(t_string::fmt("%06X", entry.to_rgb()));
    }
    write_all_lines(pal_entries, filename + palette_ext);
}

void t_filesystem::load_charset_plaintext(t_charset* chr, const t_string& filename)
{
    auto chr_lines = read_all_lines(filename + charset_ext);
    chr->remove_all();
    for (auto& line : chr_lines) {
        chr->add(line);
    }
}

void t_filesystem::load_palette_plaintext(t_palette* pal, const t_string& filename)
{
    auto pal_lines = read_all_lines(filename + palette_ext);
    pal->remove_all();
    for (auto& line : pal_lines) {
        t_string rgb = t_string("0x") + line;
        pal->add(rgb.to_int());
    }
}

bool t_filesystem::is_record_file_open()
{
    return record_file.is_open;
}

char t_filesystem::get_record_file_mode()
{
    return record_file.mode;
}

void t_filesystem::open_record_file(const t_string& filename, char mode)
{
    record_file.open(filename, mode);
}

void t_filesystem::close_record_file()
{
    record_file.close_and_save_hex_file();
}

void t_filesystem::write_record_file(const t_string& data)
{
    record_file.write(data);
}

t_string t_filesystem::read_record_file()
{
    return record_file.read();
}

bool t_filesystem::is_record_file_eof()
{
    return record_file.is_eof();
}
