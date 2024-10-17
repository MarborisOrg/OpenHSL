
// From macros.cpp, To var.cpp

#include "../macros/macros.cpp"

func let
{
public:
    std::any data;

    // سازنده برای مقداردهی به هر نوع
    template <typename T>
    let(T value)
    {
        data = value;
    }

    // عملگر << برای اضافه کردن به انتهای مقدار (در صورت رشته بودن)
    let &operator<<(const str &value)
    {
        if (data.type() == typeid(str))
        {
            std::any_cast<str>(data) += value;  // اضافه کردن به انتهای رشته
        }
        else
        {
            std::cout << "Error: Cannot use << with non-string types!" << std::endl;
        }
        return *this;
    }

    // عملگر >> برای جایگزینی مقدار
    template <typename T>
    let &operator>>(T value)
    {
        data = value;  // جایگزینی مقدار با نوع جدید
        return *this;
    }

    // عملگر برای نمایش مقدار
    friend std::ostream &operator<<(std::ostream &os, const let &obj)
    {
        // بررسی نوع و نمایش مقدار
        if (obj.data.type() == typeid(int))
        {
            os << std::any_cast<int>(obj.data);
        }
        else if (obj.data.type() == typeid(str))
        {
            os << std::any_cast<str>(obj.data);
        }
        else
        {
            os << "Unsupported type";  // در صورت عدم پشتیبانی
        }

        return os;
    }
};