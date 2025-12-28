#include "../../include/types/json_value.hpp"
#include "../../include/types/json_null.hpp"
#include "../../include/types/json_boolean.hpp"
#include "../../include/types/json_number.hpp"
#include "../../include/types/json_string.hpp"
#include "../../include/types/json_array.hpp"
#include "../../include/types/json_object.hpp"
#include <variant>

struct json_value::impl {
    using variant_t = std::variant<
        std::monostate,
        json_null,
        json_boolean,
        json_number,
        json_string,
        std::unique_ptr<json_array>,
        std::unique_ptr<json_object>
    >;

    variant_t data;

    impl() : data(json_null{}) {}
    impl(json_null v) : data(v) {}
    impl(json_boolean v) : data(v) {}
    impl(json_number v) : data(v) {}
    impl(json_string v) : data(std::move(v)) {}
    impl(std::unique_ptr<json_array> v) : data(std::move(v)) {}
    impl(std::unique_ptr<json_object> v) : data(std::move(v)) {}

    impl(const impl& other) {
        std::visit([this](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                data = json_null{};
            } 
            else if constexpr (std::is_same_v<T, std::unique_ptr<json_array>>) {
                data = std::make_unique<json_array>(*val);
            } 
            else if constexpr (std::is_same_v<T, std::unique_ptr<json_object>>) {
                data = std::make_unique<json_object>(*val);
            } 
            else {
                data = val;
            }
        }, other.data);
    }

    impl(impl&& other) noexcept : data(std::move(other.data)) {
        other.data = json_null{};
    }

    impl& operator=(const impl& other) {
        if (this != &other) {
            std::visit([this](const auto& val) {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    data = json_null{};
                } 
                else if constexpr (std::is_same_v<T, std::unique_ptr<json_array>>) {
                    data = std::make_unique<json_array>(*val);
                } 
                else if constexpr (std::is_same_v<T, std::unique_ptr<json_object>>) {
                    data = std::make_unique<json_object>(*val);
                } 
                else {
                    data = val;
                }
            }, other.data);
        }

        return *this;
    }

    impl& operator=(impl&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            other.data = json_null{};
        }
        
        return *this;
    }
};

json_value::json_value() : pimpl_(std::make_unique<impl>()) {}

json_value::json_value(std::nullptr_t) : pimpl_(std::make_unique<impl>(json_null{})) {}

json_value::json_value(bool value) : pimpl_(std::make_unique<impl>(json_boolean(value))) {}

json_value::json_value(int value) : pimpl_(std::make_unique<impl>(json_number(static_cast<double>(value)))) {}

json_value::json_value(double value) : pimpl_(std::make_unique<impl>(json_number(value))) {}

json_value::json_value(const char* value) : pimpl_(std::make_unique<impl>(json_string(value))) {}

json_value::json_value(const std::string& value) : pimpl_(std::make_unique<impl>(json_string(value))) {}

json_value::json_value(std::string&& value) : pimpl_(std::make_unique<impl>(json_string(std::move(value)))) {}

json_value::json_value(const json_value& other)
    : pimpl_(other.pimpl_ ? std::make_unique<impl>(*other.pimpl_) : std::make_unique<impl>()) {}

json_value::json_value(json_value&& other) noexcept : pimpl_(std::move(other.pimpl_)) {
    other.pimpl_ = std::make_unique<impl>();
}

json_value& json_value::operator=(const json_value& other) {
    if (this != &other) {
        pimpl_ = other.pimpl_ ? std::make_unique<impl>(*other.pimpl_) : std::make_unique<impl>();
    }

    return *this;
}

json_value& json_value::operator=(json_value&& other) noexcept {
    if (this != &other) {
        pimpl_ = std::move(other.pimpl_);
        other.pimpl_ = std::make_unique<impl>();
    }
    
    return *this;
}

json_value::~json_value() = default;

json_type json_value::type() const {
    return std::visit([](const auto& val) -> json_type {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, std::monostate> || std::is_same_v<T, json_null>) {
            return json_type::null;
        } 
        else if constexpr (std::is_same_v<T, json_boolean>) {
            return json_type::boolean;
        } 
        else if constexpr (std::is_same_v<T, json_number>) {
            return json_type::number;
        } 
        else if constexpr (std::is_same_v<T, json_string>) {
            return json_type::string;
        } 
        else if constexpr (std::is_same_v<T, std::unique_ptr<json_array>>) {
            return json_type::array;
        } 
        else if constexpr (std::is_same_v<T, std::unique_ptr<json_object>>) {
            return json_type::object;
        }
    }, pimpl_->data);
}

std::string json_value::dump(int indent, int current_indent) const {
    return std::visit([indent, current_indent](const auto& val) -> std::string {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return json_null{}.dump(indent, current_indent);
        } 
        else if constexpr (std::is_same_v<T, std::unique_ptr<json_array>>) {
            return val->dump(indent, current_indent);
        } 
        else if constexpr (std::is_same_v<T, std::unique_ptr<json_object>>) {
            return val->dump(indent, current_indent);
        } 
        else {
            return val.dump(indent, current_indent);
        }
    }, pimpl_->data);
}

json_value json_value::clone() const {
    return json_value(*this);
}

bool json_value::operator==(const json_value& other) const {
    if (type() != other.type()) return false;

    return std::visit([&other](const auto& val) -> bool {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, std::monostate> || std::is_same_v<T, json_null>) {
            return true;
        } 
        else if constexpr (std::is_same_v<T, json_boolean>) {
            return val == std::get<json_boolean>(other.pimpl_->data);
        } 
        else if constexpr (std::is_same_v<T, json_number>) {
            return val == std::get<json_number>(other.pimpl_->data);
        } 
        else if constexpr (std::is_same_v<T, json_string>) {
            return val == std::get<json_string>(other.pimpl_->data);
        } 
        else if constexpr (std::is_same_v<T, std::unique_ptr<json_array>>) {
            return *val == *std::get<std::unique_ptr<json_array>>(other.pimpl_->data);
        } 
        else if constexpr (std::is_same_v<T, std::unique_ptr<json_object>>) {
            return *val == *std::get<std::unique_ptr<json_object>>(other.pimpl_->data);
        }
        return false;
    }, pimpl_->data);
}

bool json_value::operator!=(const json_value& other) const {
    return !(*this == other);
}

bool json_value::is_null() const { return type() == json_type::null; }
bool json_value::is_boolean() const { return type() == json_type::boolean; }
bool json_value::is_number() const { return type() == json_type::number; }
bool json_value::is_string() const { return type() == json_type::string; }
bool json_value::is_array() const { return type() == json_type::array; }
bool json_value::is_object() const { return type() == json_type::object; }

json_null& json_value::as_null() {
    if (auto* p = std::get_if<json_null>(&pimpl_->data)) {
        return *p;
    }

    throw std::runtime_error("Value is not null");
}

const json_null& json_value::as_null() const {
    if (auto* p = std::get_if<json_null>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not null");
}

json_boolean& json_value::as_boolean() {
    if (auto* p = std::get_if<json_boolean>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not boolean");
}

const json_boolean& json_value::as_boolean() const {
    if (auto* p = std::get_if<json_boolean>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not boolean");
}

json_number& json_value::as_number() {
    if (auto* p = std::get_if<json_number>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not number");
}

const json_number& json_value::as_number() const {
    if (auto* p = std::get_if<json_number>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not number");
}

json_string& json_value::as_string() {
    if (auto* p = std::get_if<json_string>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not string");
}

const json_string& json_value::as_string() const {
    if (auto* p = std::get_if<json_string>(&pimpl_->data)) {
        return *p;
    }
    
    throw std::runtime_error("Value is not string");
}

json_array& json_value::as_array() {
    if (auto* p = std::get_if<std::unique_ptr<json_array>>(&pimpl_->data)) {
        return **p;
    }
    
    throw std::runtime_error("Value is not array");
}

const json_array& json_value::as_array() const {
    if (auto* p = std::get_if<std::unique_ptr<json_array>>(&pimpl_->data)) {
        return **p;
    }
    
    throw std::runtime_error("Value is not array");
}

json_object& json_value::as_object() {
    if (auto* p = std::get_if<std::unique_ptr<json_object>>(&pimpl_->data)) {
        return **p;
    }
    
    throw std::runtime_error("Value is not object");
}

const json_object& json_value::as_object() const {
    if (auto* p = std::get_if<std::unique_ptr<json_object>>(&pimpl_->data)) {
        return **p;
    }
    
    throw std::runtime_error("Value is not object");
}

json_value json_value::make_array() {
    json_value v;
    v.pimpl_->data = std::make_unique<json_array>();
    return v;
}

json_value json_value::make_object() {
    json_value v;
    v.pimpl_->data = std::make_unique<json_object>();
    return v;
}
