#ifndef LOCALHOST_SESSIONERROR_INCLUDE_HPP
#define LOCALHOST_SESSIONERROR_INCLUDE_HPP

#include <exception>
#include "deadcode.hpp"
#include "json/responce.hpp"
#include "core.hpp"

namespace local::host {
    class SessionError
        : public std::exception {
    private:
        class UnprocessedValue {
        public:
            static constexpr core::Size sk_bad_size_ { 1'000'000'000 };
        };

        DeadCode dcode_;

    public:
        bool isError() const noexcept;
        void checkOnError(const Responce &_k_responce) noexcept;
        [[nodiscard]]
        const char *what() const override;
    };
}

#endif
