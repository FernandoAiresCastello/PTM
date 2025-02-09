#include <fstream>
#include <filesystem>
#include "PTM.h"
#include "t_filesystem.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_interpreter.h"
#include "t_screen.h"

constexpr int bytes_per_line = 16;

namespace fs = std::filesystem;

t_list<t_string> t_filesystem::illegal_filenames = {
    "ROOT", "USR", "SYS", "CON", "PRN", "AUX", "NUL",
    "COM0", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "COM¹", "COM²", "COM³", 
    "LPT0", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9", "LPT¹", "LPT²", "LPT³"
};

t_string directory = "";
t_record_file record_file;

bool t_filesystem::is_valid_filename(const t_string& filename)
{
    t_string trimmed_filename = filename.trim().to_upper();

    if (trimmed_filename.empty())
        return false;
    if (trimmed_filename == "." || trimmed_filename == "..")
        return false;
    if (trimmed_filename.in(illegal_filenames))
        return false;
    if (filename.contains_any(" <>:\"/\\|?*"))
        return false;

    return true;
}

bool t_filesystem::file_exists(const t_string& filename)
{
    return 
        fs::exists(fs::path(filename.to_upper().c_str())) &&
        fs::is_regular_file(fs::path(filename.to_upper().c_str()));
}

bool t_filesystem::user_file_exists(const t_string& filename)
{
    return file_exists(t_string(USER_ROOT) + filename);
}

t_list<t_string> t_filesystem::list_user_files(const char* prefix)
{
    t_list<t_string> files;

    for (const auto& entry : fs::directory_iterator(USER_ROOT)) {
        if (fs::is_regular_file(entry.status())) {
            const auto&& path = entry.path().filename().string();
            if (prefix) {
                if (prefix[0] == '*') {
                    t_string suffix = t_string(prefix).skip(1);
                    if (!suffix.empty() && path.ends_with(suffix.c_str())) {
                        files.emplace_back(t_string(path).to_upper());
                    }
                }
                else if (path.starts_with(prefix)) {
                    files.emplace_back(t_string(path).to_upper());
                }
            }
            else {
                files.emplace_back(t_string(path).to_upper());
            }
        }
    }

    return files;
}

t_list<t_string> t_filesystem::find_user_files(const t_string& namepart)
{
    return list_user_files(namepart.to_upper().c_str());
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
        const auto&& bytes_str = line.split(' ', true);
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
    t_string path = filename.to_upper();

    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
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
    auto raw_lines = contents.split('\n', true);

    for (auto& line : raw_lines)
        lines.push_back(line.replace("\r", ""));

    return lines;
}

void t_filesystem::write_all_text(const t_string& text, const t_string& filename)
{
    std::ofstream file(filename.to_upper().c_str(), std::ios::out | std::ios::binary);
    if (!file)
        throw std::runtime_error("Could not open file");

    file.write(text.s_str().data(), text.s_str().size());
}

void t_filesystem::write_all_lines(const t_list<t_string>& lines, const t_string& filename)
{
    t_string text;

    for (auto& line : lines) {
        text += line;
        text += "\r\n";
    }

    write_all_text(text, filename);
}

bool t_filesystem::rename_file(const t_string& old_name, const t_string& new_name)
{
    try
    {
        fs::rename(old_name.to_upper().c_str(), new_name.to_upper().c_str());
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
        fs::remove(name.to_upper().c_str());
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
        fs::rename(old_name.to_upper().c_str(), new_name.to_upper().c_str());
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
        fs::remove_all(name.to_upper().c_str());
        return true;
    }
    catch (std::exception)
    {
        return false;
    }
}

bool t_filesystem::has_autoexec_file()
{
    return file_exists(USER_ROOT AUTOEXEC_FILE);
}

t_string t_filesystem::get_autoexec_file()
{
    return USER_ROOT AUTOEXEC_FILE;
}

void t_filesystem::autosave_program(t_program* prg)
{
    save_program_plaintext(prg, USER_ROOT AUTOSAVE_FILE);
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
        if (!intp->get_error().empty()) {
            prg->lines.clear();
            break;
        }
    }
}

void t_filesystem::save_charset_plaintext(t_charset* chr, const t_string& filename)
{
    t_list<t_string> chr_entries;
    for (int i = 0; i < chr->size(); i++) {
        t_binary& entry = chr->get(i);
        chr_entries.push_back(entry);
    }
    write_all_lines(chr_entries, filename.to_upper());
}

void t_filesystem::save_palette_plaintext(t_palette* pal, const t_string& filename)
{
    t_list<t_string> pal_entries;
    for (int i = 0; i < pal->size(); i++) {
        t_color& entry = pal->get(i);
        pal_entries.push_back(t_string::fmt("%06X", entry.to_rgb()));
    }
    write_all_lines(pal_entries, filename.to_upper());
}

void t_filesystem::load_charset_plaintext(t_charset* chr, const t_string& filename)
{
    auto chr_lines = read_all_lines(filename.to_upper());
    chr->remove_all();
    for (auto& line : chr_lines) {
        chr->add(line);
    }
}

void t_filesystem::load_palette_plaintext(t_palette* pal, const t_string& filename)
{
    auto pal_lines = read_all_lines(filename.to_upper());
    pal->remove_all();
    for (auto& line : pal_lines) {
        t_string rgb = t_string("0x") + line;
        pal->add(rgb.to_int());
    }
}

void t_filesystem::load_default_charset(t_charset* chr)
{
    load_charset_plaintext(chr, SYS_ROOT DEF_CHARSET_FILE);
}

void t_filesystem::load_default_palette(t_palette* pal)
{
    load_palette_plaintext(pal, SYS_ROOT DEF_PALETTE_FILE);
}

bool t_filesystem::is_record_file_open()
{
    return record_file.is_open;
}

char t_filesystem::get_record_file_mode()
{
    return record_file.mode;
}

int t_filesystem::open_record_file(const t_string& filename, char mode)
{
    return record_file.open(t_string(USER_ROOT) + filename.to_upper(), mode);
}

void t_filesystem::close_record_file()
{
    record_file.close_and_save();
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
