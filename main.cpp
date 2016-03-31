#include <iostream>
#include <stdio.h>

#include "newrelic_collector_client.h"
#include "newrelic_common.h"
#include "newrelic_transaction.h"

const char* nr_error_code(int);

int main()
{
    int err = newrelic_init("SERIAL_KEY",
                        "TESTING", "SDK", "c++11");
    std::cout << "Init: "
              << nr_error_code(err)
              << std::endl;

    long tr_id = newrelic_transaction_begin();
    std::cout << "transaction id: " << tr_id << std::endl;

    long segment_id = newrelic_segment_generic_begin(tr_id,
                                                        0,
                                                        "Create exception segment"
                                                        );
    std::cout << "segment id: " << segment_id << std::endl;

    err = newrelic_transaction_notice_error(tr_id,
                                                    "Some exception",
                                                    "Something bad happened!",
                                                    "foo, bar",
                                                    ",");
    std::cout << "transaction notice result: "
              << nr_error_code(err)
              << std::endl;

    err = newrelic_segment_end(tr_id, segment_id);
    std::cout << "Segment end: "
              << nr_error_code(err)
              << std::endl;

    err = newrelic_transaction_end(tr_id);
    std::cout << "transaction end: "
                << nr_error_code(err)
                << std::endl;


    err = newrelic_request_shutdown("Tester session going down...");
    std::cout << "Shutdown: "
              << nr_error_code(err)
                << std::endl;

    return 0;
}

const char* nr_error_code(int errcode)
{
    static char s[100];
    switch(errcode) {
        case NEWRELIC_RETURN_CODE_OK:
            return "OK";
        case NEWRELIC_RETURN_CODE_OTHER:
            return "OTHER";
        case NEWRELIC_RETURN_CODE_DISABLED:
            return "DISABLED";
        case NEWRELIC_RETURN_CODE_INVALID_PARAM:
            return "INVALID_PARAM";
        case NEWRELIC_RETURN_CODE_INVALID_ID:
            return "INVALID_ID";
        case NEWRELIC_RETURN_CODE_TRANSACTION_NOT_STARTED:
            return "TRANSACTION_NOT_STARTED";
        case NEWRELIC_RETURN_CODE_TRANSACTION_IN_PROGRESS:
            return "TRANSACTION_IN_PROGRESS";
        case NEWRELIC_RETURN_CODE_TRANSACTION_NOT_NAMED:
            return "TRANSACTION_NOT_NAMED";
        default:
            sprintf(s, "UNKNOWN: %d", errcode);
            return s;
    }
}
