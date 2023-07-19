#include "MP3parser.h"

void TextFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "information: ";
    output << frame_information << "\n";
    output << "\n";
}

void UrlFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "information: ";
    output << frame_information << "\n";
    output << "\n";
}

void CommentFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "language: ";
    output << frame_language << "\n";
    output << "description: ";
    output << frame_description << "\n";
    output << "information: ";
    output << frame_information << "\n";
    output << "\n";
}

void PopmFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "email: ";
    output << frame_email << "\n";
    output << "rating: ";
    output << frame_rating << "\n";
    output << "counter: ";
    output << frame_counter << "\n";
    output << "\n";
}

void UsltFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "language: ";
    output << frame_language << "\n";
    output << "descriptor: ";
    output << frame_descriptor << "\n";
    output << "text: ";
    output << frame_text << "\n";
    output << "\n";
}

void ComrFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "price: ";
    output << frame_price << "\n";
    output << "valid until: ";
    output << frame_valid << "\n";
    output << "url: ";
    output << frame_url << "\n";
    output << "received as: ";
    output << frame_received_as << "\n";
    output << "name of seller: ";
    output << frame_name_of_seller << "\n";
    output << "description: ";
    output << frame_description << "\n";
    output << "mime type: ";
    output << frame_mime_type << "\n";
    output << "seller logo: ";
    for (unsigned char i: frame_seller_logo) {
        output << i;
    }
    output << "\n";
}

void EncrFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "owner: ";
    output << frame_owner << "\n";
    output << "method symbol: ";
    output << frame_method_symbol << "\n";
    output << "encryption data: ";
    for (unsigned char i: frame_encryption_data) {
        output << i;
    }
    output << "\n";
}

void Equ2Frame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "inter method: ";
    output << frame_inter_method << "\n";
    output << "identification: ";
    output << frame_identification << "\n";
    output << "freq: ";
    output << frame_freq << "\n";
    output << "volume adjustment: ";
    output << frame_vol_adj << "\n";
    output << "\n";
}

void EtcoFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "time stamp format: ";
    if (frame_time_stamp_format == 1) {
        output << "Absolute time, 32 bit sized, using MPEG [MPEG] frames as unit" << "\n";
    } else {
        output << "Absolute time, 32 bit sized, using milliseconds as unit" << "\n";
    }
    for (std::pair<uint8_t, uint32_t> i: frame_events) {
        if ((i.first >= 23 && i.first <= 223) || (i.first >= 240 && i.first <= 252)) {
            output << "reserved for future use" << " ";
            output << i.second << "\n";
        } else if (i.first >= 224 && i.first <= 239) {
            output << "not predefined synch 0-F" << " ";
            output << i.second << "\n";
        } else {
            output << ETCO_content[i.first] << " " << i.second << "\n";
        }
    }
    output << "\n";
}

void GridFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "owner identifier: ";
    output << frame_owner_identifier << "\n";
    output << "group symbol: ";
    output << frame_group_symbol << "\n";
    output << "group dependent data: ";
    for (unsigned char i: frame_group_dependent_data) {
        output << i;
    }
    output << "\n";
}

void OwneFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "price paid: ";
    output << frame_price_paid << "\n";
    output << "date: ";
    output << frame_date << "\n";
    output << "seller: ";
    output << frame_seller << "\n";
    output << "\n";
}

void PcntFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "counter: ";
    output << frame_counter << "\n";
    output << "\n";
}

void RbufFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "buffer size: ";
    output << frame_buffer_size << "\n";
    output << "embedded info: ";
    output << frame_embedded_info << "\n";
    output << "offset: ";
    output << frame_offset << "\n";
    output << "\n";
}

void UserFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "language: ";
    output << frame_language << "\n";
    output << "text: ";
    output << frame_text << "\n";
    output << "\n";
}

void McdiFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "cd toc: ";
    for (unsigned char i: frame_cd_toc) {
        output << i;
    }
    output << "\n";
}

void SeekFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "minimum offset: ";
    output << frame_minimum_offset << "\n";
    output << "\n";
}

void PrivFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "owner identifier: ";
    output << frame_owner_identifier << "\n";
    output << "private data: ";
    for (unsigned char i: frame_private_data) {
        output << i;
    }
    output << "\n";
}

void PossFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "time stamp format: ";
    output << frame_time_stamp_format << "\n";
    output << "position: ";
    output << frame_position << "\n";
    output << "\n";
}

void Rva2Frame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "identification: ";
    output << frame_identification << "\n";
    output << "type of channel: ";
    output << frame_type_of_channel << "\n";
    output << "volume adjustment: ";
    output << frame_volume_adjustment << "\n";
    output << "bits representing peak: ";
    output << frame_bits_representing_peak << "\n";
    output << "peak volume: ";
    output << frame_peak_volume << "\n";
    output << "\n";
}

void SyltFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "language: ";
    output << frame_language << "\n";
    output << "time stamp format: ";
    if (frame_time_stamp_format == 0) {
        output << "Absolute time, 32 bit sized, using MPEG [MPEG] frames as unit\n";
    } else {
        output << "Absolute time, 32 bit sized, using milliseconds as unit\n";
    }
    output << "content type: ";
    output << SYLT_content[frame_content_type] << "\n";
    output << "content descriptor: ";
    output << frame_content_descriptor << "\n";
    output << "time stamp:" << "\n";
    for (auto& i: frame_time_stamp) {
        output << i.first << " " << i.second << "\n";
    }
    output << "\n";
}

void UfidFrame::OutputFrame(std::ofstream& output) {
    output << frame_name << "\n";
    output << "owner identifier: ";
    output << frame_owner_identifier << "\n";
    output << "identifier: ";
    for (unsigned char i: frame_identifier) {
        output << i;
    }
    output << "\n";
}

void ID3::Output(std::ofstream& output) {
    for (auto& frame: frames) {
        (*frame)->OutputFrame(output);
    }
}
