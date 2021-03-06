#include <gtest/gtest.h>
#include <mlio.h>

namespace mlio {

class Test_recordio_protobuf_reader : public ::testing::Test {
protected:
    Test_recordio_protobuf_reader() = default;

    ~Test_recordio_protobuf_reader() override;

protected:
    std::string const resources_path_ = "../resources/recordio/";
    std::string const complete_records_path_ = resources_path_ + "complete_records.pr";
    std::string const split_records_path_ = resources_path_ + "split_records.pr";
    std::string const corrupt_split_records_path_ = resources_path_ + "corrupted_split_records.pr";
};

Test_recordio_protobuf_reader::~Test_recordio_protobuf_reader() = default;

TEST_F(Test_recordio_protobuf_reader, test_complete_records_path)
{
    mlio::Data_reader_params prm{};
    prm.dataset.emplace_back(mlio::make_intrusive<mlio::File>(complete_records_path_));
    prm.batch_size = 1;

    auto reader = mlio::make_intrusive<mlio::Recordio_protobuf_reader>(prm);
    for (int i = 0; i < 2; i++) {
        mlio::Intrusive_ptr<mlio::Example> exm;
        while ((exm = reader->read_example()) != nullptr) {
        }
        reader->reset();
    }

    EXPECT_TRUE(true);
}

TEST_F(Test_recordio_protobuf_reader, test_split_records_path)
{
    mlio::initialize();
    mlio::Data_reader_params prm{};
    prm.dataset.emplace_back(mlio::make_intrusive<mlio::File>(split_records_path_));
    prm.batch_size = 1;

    auto reader = mlio::make_intrusive<mlio::Recordio_protobuf_reader>(prm);
    for (int i = 0; i < 2; i++) {
        mlio::Intrusive_ptr<mlio::Example> exm;
        while ((exm = reader->read_example()) != nullptr) {
        }
        reader->reset();
    }

    EXPECT_TRUE(true);
}

TEST_F(Test_recordio_protobuf_reader, test_corrupt_split_records_patH)
{
    mlio::initialize();
    // Check that the third Record is corrupt.
    mlio::Data_reader_params prm{};
    prm.dataset.emplace_back(mlio::make_intrusive<mlio::File>(corrupt_split_records_path_));
    prm.batch_size = 10;
    prm.num_prefetched_examples = 1;

    std::string error_substring = "The Record #13 in the data store";

    auto reader = mlio::make_intrusive<mlio::Recordio_protobuf_reader>(prm);
    mlio::Intrusive_ptr<mlio::Example> exm;

    // Try to read batch, should fail due to corrupt Record
    try {
        exm = reader->read_example();
        FAIL() << "Expected corrupt error exception on 3rd Record.";
    }
    catch (Data_reader_error const &corrupt_record_err) {
        EXPECT_TRUE(std::string(corrupt_record_err.what()).find(error_substring) !=
                    std::string::npos)
            << "Error thrown:" + std::string(corrupt_record_err.what());
    }
    catch (...) {
        FAIL() << "Expected corrupt error exception, not a different error.";
    }

    // Try to read batch, should fail again
    try {
        exm = reader->read_example();
        FAIL() << "Expected corrupt error exception on 3rd Record.";
    }
    catch (Data_reader_error const &corrupt_record_err) {
        EXPECT_TRUE(std::string(corrupt_record_err.what()).find(error_substring) !=
                    std::string::npos)
            << "Error thrown:" + std::string(corrupt_record_err.what());
    }
    catch (...) {
        FAIL() << "Expected corrupt error exception, not a different error.";
    }

    // Reset reader, expecting same results.
    reader->reset();

    // Try to read batch, should fail again
    try {
        exm = reader->read_example();
        FAIL() << "Expected corrupt error exception on 3rd Record.";
    }
    catch (Data_reader_error const &corrupt_record_err) {
        EXPECT_TRUE(std::string(corrupt_record_err.what()).find(error_substring) !=
                    std::string::npos)
            << "Error thrown:" + std::string(corrupt_record_err.what());
    }
    catch (...) {
        FAIL() << "Expected corrupt error exception, not a different error.";
    }
}

}  // namespace mlio
