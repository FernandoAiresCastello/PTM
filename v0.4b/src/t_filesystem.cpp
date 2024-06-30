#include <fstream>
#include <filesystem>
#include "t_filesystem.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_interpreter.h"

#define ROOT        "root\\"
#define PATH(x)     (ROOT + filename.trim().to_upper().s_str())

namespace fs = std::filesystem;

t_list<t_string> t_filesystem::illegal_filenames = {
    "CON", "PRN", "AUX", "NUL", 
    "COM0", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "COM¹", "COM²", "COM³", 
    "LPT0", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9", "LPT¹", "LPT²", "LPT³"
};

bool t_filesystem::is_valid_filename(const t_string& filename)
{
    t_string trimmed_filename = filename.trim();

    if (trimmed_filename.empty())
        return false;
    if (trimmed_filename == "." || trimmed_filename == "..")
        return false;
    if (trimmed_filename.ends_with("."))
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

    struct stat buffer;
    return (stat(PATH(filename).c_str(), &buffer) == 0);
}

t_list<t_string> t_filesystem::list_files()
{
    t_list<t_string> files;

    for (const auto& entry : fs::directory_iterator(ROOT)) {
        if (fs::is_regular_file(entry.status())) {
            const auto&& path = entry.path().filename().string();
            files.emplace_back(path);
        }
    }

    return files;
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

void t_filesystem::write_all_text(t_string text, const t_string& filename)
{
    std::ofstream file(PATH(filename), std::ios::out | std::ios::binary);
    if (!file)
        throw std::runtime_error("Could not open file");

    file.write(text.s_str().data(), text.s_str().size());
}

void t_filesystem::save_program(t_program* prg, const t_string& filename)
{
    t_string output;

    for (auto& raw_line : prg->lines) {
        const auto& line = raw_line.second.src;
        output += line;
        output += "\r\n";
    }

    write_all_text(output, filename);
}

void t_filesystem::load_program(t_interpreter* intp, t_program* prg, const t_string& filename)
{
    auto src_lines = read_all_lines(filename);

    prg->lines.clear();

    for (auto& src_line : src_lines) {
        intp->interpret_line(src_line, true);
        if (!intp->get_last_error().empty()) {
            prg->lines.clear();
            break;
        }
    }
}
