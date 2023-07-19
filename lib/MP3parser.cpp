#include "MP3parser.h"

uint32_t ConvertFromSyncToDec(const std::string& number) {
    uint32_t answer = 0;
    uint32_t number_len = number.length();
    uint32_t cnt = 0;

    for (int i = 1; i < number_len; i++) {
        if (i % 8 != 0) {
            answer += (number[number_len - i] - '0') * static_cast<uint32_t>(pow(2, i - 1 - cnt));
        } else {
            cnt++;
        }
    }
    return answer;
}

uint64_t ConvertFromBinToDec(const std::string& number) {
    uint64_t answer = 0;
    uint32_t number_len = number.length();

    for (int i = 1; i <= number_len; i++) {
        answer += (number[number_len - i] - '0') * static_cast<uint32_t>(pow(2, i - 1));
    }
    return answer;
}

void Header::HeaderParser(std::ifstream& input) {
    uint8_t current_byte;
    int counter = 0;
    std::string size_of_file;
    while (counter != ID3::ID3_header_size) {
        current_byte = input.get();
        counter++;
        if (counter == 4) {
            ID3_version = current_byte;
        } else if (counter == 5) {
            ID3_revision = current_byte;
        } else if (counter == 6) {
            std::bitset<8> fl(current_byte);
            for (int i = 0; i < 4; i++) {
                if (fl[7 - i] == 1) {
                    flags[i] = true;
                }
            }
        } else if (counter > 6) {
            std::bitset<8> fl(current_byte);
            size_of_file += fl.to_string();
        }
    }
    ID3_size = ConvertFromSyncToDec(size_of_file);
}

std::vector<bool> Header::GetFlags() const {
    return flags;
}

void SkipExtendedHeader(std::ifstream& input) {
    std::string size_of_extended_header;
    uint8_t current_byte;
    for (int i = 0; i < 4; i++) {
        current_byte = input.get();
        std::bitset<8> fl(current_byte);
        size_of_extended_header += fl.to_string();
    }
    uint32_t size = ConvertFromSyncToDec(size_of_extended_header);
    input.seekg(size, std::ios::cur);
}

std::string Frame::GetFrameName() const {
    return frame_name;
}

void TextFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    int counter = 1;
    current_byte = input.get();
    frame_text_encoding = current_byte;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        frame_information += static_cast<char>(current_byte);
    }
}

void UrlFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    int counter = 0;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        frame_information += static_cast<char>(current_byte);
    }
}

void CommentFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    int counter = 0;
    bool flag_zero = false;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0 && !flag_zero) {
            flag_zero = true;
            continue;
        }
        if (counter >= 2 && counter <= 4) {
            frame_language += static_cast<char>(current_byte);
        } else if (counter > 4 && !flag_zero) {
            frame_description += static_cast<char>(current_byte);
        } else if (counter > 4) {
            frame_information += static_cast<char>(current_byte);
        }
    }
}

void PopmFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    int counter = 0;
    bool flag_zero = false;
    bool flag_rating = false;
    std::string frame_counter_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            flag_zero = true;
            continue;
        }
        if (!flag_zero) {
            frame_email += static_cast<char>(current_byte);
        } else if (!flag_rating) {
            frame_rating = current_byte;
            flag_rating = true;
        } else {
            std::bitset<8> fl(current_byte);
            frame_counter_ += fl.to_string();
        }
    }
    frame_counter = ConvertFromBinToDec(frame_counter_);
}

void UsltFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 1;
    bool flag_zero = false;
    current_byte = input.get();
    frame_text_encoding = current_byte;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0 && !flag_zero) {
            flag_zero = true;
            continue;
        }
        if (counter >= 2 && counter <= 4) {
            frame_language += static_cast<char>(current_byte);
        } else if (counter > 4 && !flag_zero) {
            frame_descriptor += static_cast<char>(current_byte);
        } else if (counter > 4) {
            frame_text += static_cast<char>(current_byte);
        }
    }
}

void ComrFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 1;
    uint8_t counter_zero = 0;
    current_byte = input.get();
    frame_text_encoding = current_byte;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            counter_zero++;
            continue;
        }
        if (counter_zero == 0) {
            frame_price += static_cast<char>(current_byte);
        } else if (counter_zero == 1) {
            frame_valid += static_cast<char>(current_byte);
        } else if (counter_zero == 2) {
            frame_url += static_cast<char>(current_byte);
        } else if (counter_zero == 3) {
            frame_received_as = current_byte;
            counter_zero++;
        } else if (counter_zero == 4) {
            frame_name_of_seller += static_cast<char>(current_byte);
        } else if (counter_zero == 5) {
            frame_description += static_cast<char>(current_byte);
        } else if (counter_zero == 6) {
            frame_mime_type += static_cast<char>(current_byte);
        } else {
            frame_seller_logo.push_back(current_byte);
        }
    }
}

void EncrFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    uint8_t counter_zero = 0;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            counter_zero++;
            continue;
        }
        if (counter_zero == 0) {
            frame_owner += static_cast<char>(current_byte);
        } else if (counter_zero == 1) {
            frame_method_symbol = current_byte;
            counter_zero++;
        } else {
            frame_encryption_data.push_back(current_byte);
        }
    }
}

void Equ2Frame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    uint8_t counter_zero = 0;
    std::string frame_freq_;
    std::string frame_vol_adj_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            counter_zero++;
            continue;
        }
        if (counter_zero == 0) {
            frame_inter_method = current_byte;
            counter_zero++;
        } else if (counter_zero == 1) {
            frame_identification += static_cast<char>(current_byte);
        } else if (counter_zero == 2 || counter_zero == 3) {
            std::bitset<8> fl(current_byte);
            frame_freq_ += fl.to_string();
            counter_zero++;
        } else {
            std::bitset<8> fl(current_byte);
            frame_vol_adj_ += fl.to_string();
        }
    }
    frame_freq = ConvertFromBinToDec(frame_freq_);
    frame_vol_adj = ConvertFromBinToDec(frame_vol_adj_);
}

void EtcoFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    current_byte = input.get();
    frame_time_stamp_format = current_byte;
    current_byte = input.get();
    uint8_t frame_type_event = current_byte;
    std::string frame_time_stamp_;
    uint32_t frame_time_stamp;
    for (int i = 1; i < frame_size - 1; i++) {
        current_byte = input.get();
        if (i % 5 == 0) {
            frame_time_stamp = ConvertFromBinToDec(frame_time_stamp_);
            frame_events.emplace_back(frame_type_event, frame_time_stamp);
            frame_type_event = current_byte;
        } else {
            std::bitset<8> fl(current_byte);
            frame_time_stamp_ += fl.to_string();
        }
    }
    frame_time_stamp = ConvertFromBinToDec(frame_time_stamp_);
    frame_events.emplace_back(frame_type_event, frame_time_stamp);
}

void GridFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    uint8_t counter_zero = 0;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            counter_zero++;
            continue;
        }
        if (counter_zero == 0) {
            frame_owner_identifier += static_cast<char>(current_byte);
        } else if (counter_zero == 1) {
            frame_group_symbol = current_byte;
            counter_zero++;
        } else {
            frame_group_dependent_data.push_back(current_byte);
        }
    }
}

void OwneFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 1;
    uint8_t counter_zero = 1;
    current_byte = input.get();
    frame_text_encoding = current_byte;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            counter_zero++;
            continue;
        }
        if (counter_zero == 1) {
            frame_price_paid += static_cast<char>(current_byte);
        } else if (counter_zero == 2) {
            frame_date += static_cast<char>(current_byte);
        } else {
            frame_seller += static_cast<char>(current_byte);
        }
    }
}

void PcntFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    std::string frame_counter_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        std::bitset<8> fl(current_byte);
        frame_counter_ += fl.to_string();
    }
    frame_counter = ConvertFromBinToDec(frame_counter_);
}

void RbufFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    std::string frame_buffer_size_;
    std::string frame_offset_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (counter >= 1 && counter <= 3) {
            std::bitset<8> fl(current_byte);
            frame_buffer_size_ += fl.to_string();
        } else if (counter == 4) {
            std::bitset<8> fl(current_byte);
            frame_embedded_info = fl[0];
        } else {
            std::bitset<8> fl(current_byte);
            frame_offset_ += fl.to_string();
        }
    }
    frame_buffer_size = ConvertFromBinToDec(frame_buffer_size_);
    frame_offset = ConvertFromBinToDec(frame_offset_);
    if (frame_embedded_info) {
        input.seekg(frame_offset, std::ios::cur);
    }
}

void UserFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 1;
    current_byte = input.get();
    frame_text_encoding = current_byte;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (counter >= 2 && counter <= 4) {
            frame_language += static_cast<char>(current_byte);
        } else {
            frame_text += static_cast<char>(current_byte);
        }
    }
}

void McdiFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        frame_cd_toc.push_back(current_byte);
    }
}

void SeekFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    std::string frame_minimum_offset_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        frame_minimum_offset_ += static_cast<char>(current_byte);
    }
    frame_minimum_offset = ConvertFromBinToDec(frame_minimum_offset_);
    input.seekg(frame_minimum_offset, std::ios::cur);
}

void PrivFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    bool flag_zero = false;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            flag_zero = true;
            continue;
        }
        if (!flag_zero) {
            frame_owner_identifier += static_cast<char>(current_byte);
        } else {
            frame_private_data.push_back(current_byte);
        }
    }
}

void PossFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    std::string frame_position_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (counter == 1) {
            frame_time_stamp_format = current_byte;
        } else {
            std::bitset<8> fl(current_byte);
            frame_position_ += fl.to_string();
        }
    }
    frame_position = ConvertFromBinToDec(frame_position_);
}

void Rva2Frame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    bool flag_zero = false;
    uint32_t counter_sec = 0;
    std::string frame_volume_adjustment_;
    std::string frame_peak_volume_;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            flag_zero = true;
            continue;
        }
        if (flag_zero) {
            counter_sec++;
        }
        if (!flag_zero) {
            frame_identification += static_cast<char>(current_byte);
        } else if (counter_sec == 1) {
            frame_type_of_channel = current_byte;
        } else if (counter_sec == 2 || counter_sec == 3) {
            std::bitset<8> fl(current_byte);
            frame_volume_adjustment_ += fl.to_string();
        } else if (counter_sec == 4) {
            frame_bits_representing_peak = current_byte;
        } else {
            std::bitset<8> fl(current_byte);
            frame_peak_volume_ += fl.to_string();
        }
    }
    frame_volume_adjustment = ConvertFromBinToDec(frame_volume_adjustment_);
    frame_peak_volume = ConvertFromBinToDec(frame_peak_volume_);
}

void SyltFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 1;
    bool flag_zero = false;
    current_byte = input.get();
    frame_text_encoding = current_byte;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            flag_zero = true;
            continue;
        }
        if (counter >= 2 && counter <= 4) {
            frame_language += static_cast<char>(current_byte);
        } else if (counter == 5) {
            frame_time_stamp_format = current_byte;
        } else if (counter == 6) {
            frame_content_type = current_byte;
        } else if (!flag_zero) {
            frame_content_descriptor += static_cast<char>(current_byte);
        } else {
            break;
        }
    }
    flag_zero = false;
    uint8_t breakpoint = current_byte;
    std::string name;
    std::string number_;
    uint64_t number = 0;
    while (counter < frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 0) {
            flag_zero = true;
        }

        if (current_byte == breakpoint) {
            flag_zero = false;
            number = ConvertFromBinToDec(number_);
            frame_time_stamp.emplace_back(number, name);
            name = "";
            number_ = "";
        } else {
            if (!flag_zero) {
                name += static_cast<char>(current_byte);
            } else {
                std::bitset<8> fl(current_byte);
                number_ += fl.to_string();
            }
        }
    }
    number = ConvertFromBinToDec(number_);
    frame_time_stamp.emplace_back(number, name);
}

void UfidFrame::ParseFrameInformation(std::ifstream& input) {
    uint8_t current_byte;
    uint32_t counter = 0;
    bool flag_zero = false;
    while (counter != frame_size) {
        current_byte = input.get();
        counter++;
        if (current_byte == 1) {
            flag_zero = true;
            continue;
        }
        if (!flag_zero) {
            frame_owner_identifier += static_cast<char>(current_byte);
        } else {
            frame_identifier.push_back(current_byte);
        }
    }
}

std::shared_ptr<Frame*> ParseFrame(std::ifstream& input) {
    Frame* new_frame = nullptr;
    uint8_t current_byte;
    uint32_t frame_size = 0;
    uint8_t counter = 0;
    std::vector<bool> flags(8, false);
    std::string size_of_frame;
    std::string frame_name;
    bool is_frame = false;

    while (counter != ID3::ID3_header_size) {
        current_byte = input.get();
        counter++;
        if (counter >= 1 && counter <= 4) {
            frame_name += static_cast<char>(current_byte);
        } else if (counter >= 5 && counter <= 8) {
            std::bitset<8> fl(current_byte);
            size_of_frame += fl.to_string();
        } else if (counter == 9) {
            std::bitset<8> fl(current_byte);
            for (int i = 0; i < 3; i++) {
                if (fl[6 - i] == 1) {
                    flags[i] = true;
                }
            }
        } else {
            std::bitset<8> fl(current_byte);
            flags[3] = fl[6];
            flags[4] = fl[3];
            flags[5] = fl[2];
            flags[6] = fl[1];
            flags[7] = fl[0];
        }
    }
    frame_size = ConvertFromSyncToDec(size_of_frame);
    for (char i: frame_name) {
        if ((i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9')) {
            continue;
        } else {
            ID3::end_of_frames = true;
            input.seekg(-10, std::ios::cur);
            return nullptr;
        }
    }
    if (frame_ban_list.find(frame_name) != frame_ban_list.end()) {
        input.seekg(frame_size, std::ios::cur);
        return nullptr;
    }
    if (frame_name[0] == 'T') {
        new_frame = new TextFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name[0] == 'W') {
        new_frame = new UrlFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "COMM") {
        new_frame = new CommentFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "POPM") {
        new_frame = new PopmFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "USLT") {
        new_frame = new UsltFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "COMR") {
        new_frame = new ComrFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "ENCR") {
        new_frame = new EncrFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "EQU2") {
        new_frame = new Equ2Frame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "ETCO") {
        new_frame = new EtcoFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "GRID") {
        new_frame = new GridFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "OWNE") {
        new_frame = new OwneFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "PCNT") {
        new_frame = new PcntFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "RBUF") {
        new_frame = new RbufFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "USER") {
        new_frame = new UserFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "MCDI") {
        new_frame = new McdiFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "SEEK") {
        new_frame = new SeekFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "PRIV") {
        new_frame = new PrivFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "POSS") {
        new_frame = new PossFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "RVA2") {
        new_frame = new Rva2Frame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "SYLT") {
        new_frame = new SyltFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    } else if (frame_name == "UFID") {
        new_frame = new UfidFrame(frame_name, frame_size, flags);
        new_frame->ParseFrameInformation(input);
    }
    return std::make_shared<Frame*>(new_frame);
}


void ID3::Parse(std::ifstream& input) {
    ID3_header.HeaderParser(input);
    if (ID3_header.GetFlags()[1]) {
        SkipExtendedHeader(input);
    }
    while (!input.eof()) {
        std::shared_ptr<Frame*> new_frame = ParseFrame(input);
        if (end_of_frames) {
            break;
        }
        if (new_frame != nullptr) {
            frames.push_back(new_frame);
        }
    }
}

void MP3::Load(const std::string& path) {
    std::ifstream input(path, std::ios::binary);
    ID3 parser;
    parser.Parse(input);
    Frame* TPE1 = parser.GetFrame("TPE1");
    Frame* TIT2 = parser.GetFrame("TIT2");
    Frame* TALB = parser.GetFrame("TALB");
    if (TPE1 != nullptr) {
        author = TPE1->GetStringInformation("information");
        delete TPE1;
    }
    if (TIT2 != nullptr) {
        name = TIT2->GetStringInformation("information");
        delete TIT2;
    }
    if (TALB != nullptr) {
        album = TALB->GetStringInformation("information");
        delete TALB;
    }
    std::cout << author << "\n" << name << "\n" << album;
}