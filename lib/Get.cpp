#include "MP3parser.h"

Frame* ID3::GetFrame(const std::string& frame_name) {
    for (auto& frame: frames) {
        if ((*frame)->GetFrameName() == frame_name) {
            return (*frame);
        }
    }
    return nullptr;
}

const std::string& TextFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "information") {
        return frame_information;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& UrlFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "information") {
        return frame_information;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& CommentFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "language") {
        return frame_language;
    } else if (name_of_field == "description") {
        return frame_description;
    } else if (name_of_field == "information") {
        return frame_information;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& PopmFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "email") {
        return frame_email;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& UsltFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "language") {
        return frame_language;
    } else if (name_of_field == "descriptor") {
        return frame_descriptor;
    } else if (name_of_field == "text") {
        return frame_text;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& ComrFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "price") {
        return frame_price;
    } else if (name_of_field == "valid") {
        return frame_valid;
    } else if (name_of_field == "url") {
        return frame_url;
    } else if (name_of_field == "name of seller") {
        return frame_name_of_seller;
    } else if (name_of_field == "description") {
        return frame_description;
    } else if (name_of_field == "mime type") {
        return frame_mime_type;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& EncrFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "owner") {
        return frame_owner;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& Equ2Frame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "identification") {
        return frame_identification;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& GridFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "owner identifier") {
        return frame_owner_identifier;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& OwneFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "price paid") {
        return frame_price_paid;
    } else if (name_of_field == "date") {
        return frame_date;
    } else if (name_of_field == "seller") {
        return frame_seller;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& UserFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "language") {
        return frame_language;
    } else if (name_of_field == "text") {
        return frame_text;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& PrivFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "owner identifier") {
        return frame_owner_identifier;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& Rva2Frame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "identification") {
        return frame_identification;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& SyltFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "language") {
        return frame_language;
    } else if (name_of_field == "content descriptor") {
        return frame_content_descriptor;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

const std::string& UfidFrame::GetStringInformation(const std::string& name_of_field) const {
    if (name_of_field == "owner identifier") {
        return frame_owner_identifier;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void TextFrame::SetStringInformation(const std::string& name_of_filed, const std::string& new_value) {
    if (name_of_filed == "information") {
        frame_information = new_value;
    } else {
        throw std::invalid_argument("No such field");
    }
}

void UrlFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "information") {
        frame_information = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}
