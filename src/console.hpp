
#include "stackstrategy.hpp"
#include "cmath"

namespace rpn_engine
{

    /**
     * @brief Mode of the display format.
     *
     */
    enum class DisplayMode
    {
        fixed,      ///< display as : ####.####
        scientific, ///< Display as : 0.MMMM (-)EE
        engineering ///< Same as scientific, but exponent part is an integer multiple of 3.
    };

    class Console
    {
    public:
        Console();
        virtual ~Console();
        bool GetIsFuncKeyPressed();
        void SetIsFuncKeyPressed(bool state);
        void Input(rpn_engine::Op key);
        void GetText(char display_text[]);
        uint8_t GetDecimalPointPosition();

    private:
        FRIEND_TEST(Console, ModeTest);

        StackStrategy<std::complex<double>> engine_;
        bool is_func_key_pressed_;
        DisplayMode display_mode_;
    };
}