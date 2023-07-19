#include "MP3parser.h"

void CommentFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "language") {
        frame_language = new_value;
    } else if (name_of_field == "description") {
        frame_description = new_value;
    } else if (name_of_field == "information") {
        frame_information = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void PopmFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "email") {
        frame_email = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void UsltFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "language") {
        frame_language = new_value;
    } else if (name_of_field == "descriptor") {
        frame_descriptor = new_value;
    } else if (name_of_field == "text") {
        frame_text = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void ComrFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "price") {
        frame_price = new_value;
    } else if (name_of_field == "valid") {
        frame_valid = new_value;
    } else if (name_of_field == "url") {
        frame_url = new_value;
    } else if (name_of_field == "name of seller") {
        frame_name_of_seller = new_value;
    } else if (name_of_field == "description") {
        frame_description = new_value;
    } else if (name_of_field == "mime type") {
        frame_mime_type = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void EncrFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "owner") {
        frame_owner = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void Equ2Frame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "identification") {
        frame_identification = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void GridFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "owner identifier") {
        frame_owner_identifier = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void OwneFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "price paid") {
        frame_price_paid = new_value;
    } else if (name_of_field == "date") {
        frame_date = new_value;
    } else if (name_of_field == "seller") {
        frame_seller = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void UserFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "language") {
        frame_language = new_value;
    } else if (name_of_field == "text") {
        frame_text = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void PrivFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "owner identifier") {
        frame_owner_identifier = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void Rva2Frame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "identification") {
        frame_identification = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void SyltFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "language") {
        frame_language = new_value;
    } else if (name_of_field == "content descriptor") {
        frame_content_descriptor = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}

void UfidFrame::SetStringInformation(const std::string& name_of_field, const std::string& new_value) {
    if (name_of_field == "owner identifier") {
        frame_owner_identifier = new_value;
    } else {
        throw std::invalid_argument("No such filed");
    }
}
