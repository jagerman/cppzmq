#include <gtest/gtest.h>
#include <zmq.hpp>

TEST (message, constructor_default)
{
    const zmq::message_t message;
    ASSERT_EQ (0u, message.size ());
}

const char* const data = "Hi";

TEST (message, constructor_iterators)
{
    const std::string hi (data);
    const zmq::message_t hi_msg (hi.begin (), hi.end ());
    ASSERT_EQ (2u, hi_msg.size ());
    ASSERT_EQ (0, memcmp (data, hi_msg.data (), 2));
}

TEST (message, constructor_pointer_size)
{
    const std::string hi (data);
    const zmq::message_t hi_msg (hi.data (), hi.size ());
    ASSERT_EQ (2u, hi_msg.size ());
    ASSERT_EQ (0, memcmp (data, hi_msg.data (), 2));
}

TEST (message, constructor_char_array) {
    const zmq::message_t hi_msg (data, strlen (data));
    ASSERT_EQ (2u, hi_msg.size ());
    ASSERT_EQ (0, memcmp (data, hi_msg.data (), 2));
}

#if defined(ZMQ_BUILD_DRAFT_API) && defined(ZMQ_CPP11)
TEST (message, constructor_container)
{
    const std::string hi (data);
    zmq::message_t hi_msg (hi);
    ASSERT_EQ (2u, hi_msg.size ());
    ASSERT_EQ (0, memcmp (data, hi_msg.data (), 2));
}
#endif

#ifdef ZMQ_HAS_RVALUE_REFS
TEST (message, constructor_move)
{
    zmq::message_t hi_msg (zmq::message_t(data, strlen (data)));
}
#endif

TEST (message, equality_self) {
    const zmq::message_t hi_msg (data, strlen (data));
    ASSERT_EQ (hi_msg, hi_msg);
}

TEST (message, equality_equal) {
    const zmq::message_t hi_msg_a (data, strlen (data));
    const zmq::message_t hi_msg_b (data, strlen (data));
    ASSERT_EQ (hi_msg_a, hi_msg_b);
}

TEST (message, equality_non_equal) {
    const zmq::message_t msg_a ("Hi", 2);
    const zmq::message_t msg_b ("Hello", 5);
    ASSERT_NE (msg_a, msg_b);
}

