#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <string>

const static std::unordered_set<std::string> frame_ban_list = {
        "AENC", "APIC", "ASPI", "GEOB", "MCDI", "MLLT", "MLLT", "RVRB", "SIGN", "SYTC", "TFLT", "TMED"
};

static std::unordered_map<uint8_t, std::string> SYLT_content = {
        {0, "other"},
        {1, "lyrics"},
        {2, "text transcription"},
        {3, "movement/part name"},
        {4, "event"},
        {5, "chord"},
        {6, "trivia/\'pop up\' information"},
        {7, "URL to webpage"},
        {8, "URL to image"}
};

static std::unordered_map<uint8_t, std::string> ETCO_content = {
        {0,   "padding(has no meaning)"},
        {1,   "end of initial silence"},
        {2,   "intro start"},
        {3,   "main part start"},
        {4,   "outro start"},
        {5,   "outro end"},
        {6,   "verse start"},
        {7,   "refrain start"},
        {8,   "interlude start"},
        {9,   "theme start"},
        {10,  "variation start"},
        {11,  "key change"},
        {12,  "time change"},
        {13,  "momentary unwanted noise (Snap, Crackle & Pop)"},
        {14,  "sustained noise"},
        {15,  "sustained noise end"},
        {16,  "intro end"},
        {17,  "main part end"},
        {18,  "verse end"},
        {19,  "refrain end"},
        {20,  "theme end"},
        {21,  "profanity"},
        {22,  "profanity end"},
        {253, "audio end (start of silence)"},
        {254, "audio file ends"},
        {255, "one more byte of events follows"}
};

class Header {
private:
    std::string identifier = "ID3";
    uint8_t ID3_version;
    uint8_t ID3_revision;
    std::vector<bool> flags = std::vector<bool>(4, false);
    uint32_t ID3_size;
public:
    void HeaderParser(std::ifstream& input);

    std::vector<bool> GetFlags() const;
};

class Frame {
protected:
    std::string frame_name;
    uint32_t frame_size;
    std::vector<bool> flags = std::vector<bool>(8, false);
public:
    Frame() {
        frame_size = 0;
        frame_name = "";
    }

    virtual ~Frame() = default;

    Frame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_) :
            frame_name(frame_name_), frame_size(frame_size_), flags(flags_) {}

    virtual void ParseFrameInformation(std::ifstream& input) = 0;

    virtual void OutputFrame(std::ofstream& output) = 0;

    virtual const std::string& GetStringInformation(const std::string& name_of_field) const { return "?"; };

    virtual void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) {};

    std::string GetFrameName() const;
};

class TextFrame : public Frame {
private:
    uint8_t frame_text_encoding = 0;
    std::string frame_information;
public:
    TextFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class UrlFrame : public Frame {
private:
    std::string frame_information;
public:
    UrlFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class CommentFrame : public Frame {
private:
    std::string frame_language;
    std::string frame_description;
    std::string frame_information;
public:
    CommentFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class PopmFrame : public Frame {
private:
    std::string frame_email;
    uint8_t frame_rating = 0;
    uint64_t frame_counter = 0;
public:
    PopmFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class UsltFrame : public Frame {
private:
    uint8_t frame_text_encoding = 0;
    std::string frame_language;
    std::string frame_descriptor;
    std::string frame_text;
public:
    UsltFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class ComrFrame : public Frame {
private:
    uint8_t frame_text_encoding = 0;
    std::string frame_price;
    std::string frame_valid;
    std::string frame_url;
    uint8_t frame_received_as = 0;
    std::string frame_name_of_seller;
    std::string frame_description;
    std::string frame_mime_type;
    std::vector<uint8_t> frame_seller_logo;
public:
    ComrFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class EncrFrame : public Frame {
private:
    std::string frame_owner;
    uint8_t frame_method_symbol = 0;
    std::vector<uint8_t> frame_encryption_data;
public:
    EncrFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class Equ2Frame : public Frame {
private:
    uint8_t frame_inter_method = 0;
    std::string frame_identification;
    uint16_t frame_freq = 0;
    uint16_t frame_vol_adj = 0;
public:
    Equ2Frame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class EtcoFrame : public Frame {
private:
    uint8_t frame_time_stamp_format = 0;
    std::vector<std::pair<uint8_t, uint32_t>> frame_events;
public:
    EtcoFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;
};

class GridFrame : public Frame {
private:
    std::string frame_owner_identifier;
    uint8_t frame_group_symbol = 0;
    std::vector<uint8_t> frame_group_dependent_data;
public:
    GridFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class OwneFrame : public Frame {
private:
    uint8_t frame_text_encoding = 0;
    std::string frame_price_paid;
    std::string frame_date;
    std::string frame_seller;
public:
    OwneFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class PcntFrame : public Frame {
private:
    uint64_t frame_counter = 0;
public:
    PcntFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;
};

class RbufFrame : public Frame {
private:
    uint16_t frame_buffer_size = 0;
    bool frame_embedded_info = false;
    uint32_t frame_offset = 0;
public:
    RbufFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;
};

class UserFrame : public Frame {
private:
    uint8_t frame_text_encoding = 0;
    std::string frame_language;
    std::string frame_text;
public:
    UserFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class McdiFrame : public Frame {
private:
    std::vector<uint8_t> frame_cd_toc;
public:
    McdiFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;
};

class SeekFrame : public Frame {
private:
    uint32_t frame_minimum_offset = 0;
public:
    SeekFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;
};

class PrivFrame : public Frame {
private:
    std::string frame_owner_identifier;
    std::vector<uint8_t> frame_private_data;
public:
    PrivFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class PossFrame : public Frame {
private:
    uint8_t frame_time_stamp_format = 0;
    uint64_t frame_position = 0;
public:
    PossFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;
};

class Rva2Frame : public Frame {
private:
    std::string frame_identification;
    uint8_t frame_type_of_channel = 0;
    uint16_t frame_volume_adjustment = 0;
    uint8_t frame_bits_representing_peak = 0;
    uint64_t frame_peak_volume = 0;
public:
    Rva2Frame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class SyltFrame : public Frame {
private:
    uint8_t frame_text_encoding = 0;
    std::string frame_language;
    uint8_t frame_time_stamp_format = 0;
    uint8_t frame_content_type = 0;
    std::string frame_content_descriptor;
    std::vector<std::pair<uint64_t, std::string>> frame_time_stamp;
public:
    SyltFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class UfidFrame : public Frame {
private:
    std::string frame_owner_identifier;
    std::vector<uint8_t> frame_identifier;
public:
    UfidFrame(const std::string& frame_name_, uint32_t frame_size_, const std::vector<bool>& flags_)
            : Frame(frame_name_, frame_size_, flags_) {}

    void ParseFrameInformation(std::ifstream& input) override;

    void OutputFrame(std::ofstream& output) override;

    const std::string& GetStringInformation(const std::string& name_of_field) const override;

    void SetStringInformation(const std::string& name_of_filed, const std::string& new_value) override;
};

class ID3 {
private:
    Header ID3_header;
    std::vector<std::shared_ptr<Frame*>> frames;
public:
    ID3() = default;

    ~ID3() = default;

    ID3(const ID3& other) {
        ID3_header = other.ID3_header;
        frames = other.frames;
    }

    ID3& operator=(const ID3& other) {
        if (this == &other) {
            return *this;
        }
        ID3_header = other.ID3_header;
        frames = other.frames;
        return *this;
    }

    const static uint8_t ID3_header_size = 10;

    inline static bool end_of_frames = false;

    void Parse(std::ifstream& input);

    void Output(std::ofstream& output);

    Frame* GetFrame(const std::string& frame_name);
};

std::shared_ptr<Frame*> ParseFrame(std::ifstream& input);

void SkipExtendedHeader(std::ifstream& input);

class MP3 {
public:
    std::string name = "no name";
    std::string album = "no album";
    std::string author = "no author";
    void Load(const std::string& path);
};
