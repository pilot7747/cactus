#ifndef CACTUS_REQUEST_PARSER_HPP
#define CACTUS_REQUEST_PARSER_HPP
#include <tuple>

namespace HTTP {
    namespace HttpServer {

        struct TRequest;

/// Parser for incoming requests.
        class TRequestParser
        {
        public:
            /// Construct ready to parse the request method.
            TRequestParser();

            /// Reset to initial parser state.
            void Reset();

            /// Result of parse.
            enum ResultType { good, bad, indeterminate };

            /// Parse some data. The enum return value is good when a complete request has
            /// been parsed, bad if the data is invalid, indeterminate when more data is
            /// required. The InputIterator return value indicates how much of the input
            /// has been consumed.
            template <typename InputIterator>
            std::tuple<ResultType, InputIterator> Parse(TRequest &req,
                                                         InputIterator begin, InputIterator end)
            {
                while (begin != end)
                {
                    ResultType result = Consume(req, *begin++);
                    if (result == good || result == bad)
                        return std::make_tuple(result, begin);
                }
                return std::make_tuple(indeterminate, begin);
            }

        private:
            /// Handle the next character of input.
            ResultType Consume(TRequest &req, char input);

            /// Check if a byte is an HTTP character.
            static bool is_char(int c);

            /// Check if a byte is an HTTP control character.
            static bool is_ctl(int c);

            /// Check if a byte is defined as an HTTP tspecial character.
            static bool is_tspecial(int c);

            /// Check if a byte is a digit.
            static bool is_digit(int c);

            /// The current state of the parser.
            enum state
            {
                method_start,
                method,
                uri,
                http_version_h,
                http_version_t_1,
                http_version_t_2,
                http_version_p,
                http_version_slash,
                http_version_major_start,
                http_version_major,
                http_version_minor_start,
                http_version_minor,
                expecting_newline_1,
                header_line_start,
                header_lws,
                header_name,
                space_before_header_value,
                header_value,
                expecting_newline_2,
                expecting_newline_3
            } state_;
        };

    } // namespace Server
} // namespace http
#endif //CACTUS_REQUEST_PARSER_HPP
