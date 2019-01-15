#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <exception>
#include <mutex>
#include <condition_variable>

// #define io_service io_service

namespace asio = boost::asio;
using boost::asio::ip::tcp;

struct sensor_reading {
    sensor_reading() = default;
    sensor_reading(const sensor_reading & ) = default;
    sensor_reading & operator =(const sensor_reading & ) = default;
    ~sensor_reading() = default;
    std::size_t length;
    double rotation_pitch;
    double rotation_roll;
    double rotation_yaw;
    double rotation_rate_x;
    double rotation_rate_y;
    double rotation_rate_z;
    double quaternion_x;
    double quaternion_y;
    double quaternion_z;
    double quaternion_w;
    double raw_acceleration_x;
    double raw_acceleration_y;
    double raw_acceleration_z;
    double linear_acceleration_x;
    double linear_acceleration_y;
    double linear_acceleration_z;
    double gravity_x;
    double gravity_y;
    double gravity_z;
    double magnetic_heading;
    double true_heading;
    double heading_accuracy;
    double magnetometer_x;
    double magnetometer_y;
    double magnetometer_z;
    bool magnetometer_data_valid;
    void print2() {
        std::cout
            << "{" << std::endl
            << std::string() + "\"length\":"  << (length) << "," << std::endl
            << std::string() + "\"rotation_pitch\":"  << (rotation_pitch) << "," << std::endl
            << std::string() + "\"rotation_roll\":"  << (rotation_roll) << "," << std::endl
            << std::string() + "\"rotation_yaw\":"  << (rotation_yaw) << "," << std::endl
            << std::string() + "\"rotation_rate_x\":"  << (rotation_rate_x) << "," << std::endl
            << std::string() + "\"rotation_rate_y\":"  << (rotation_rate_y) << "," << std::endl
            << std::string() + "\"rotation_rate_z\":"  << (rotation_rate_z) << "," << std::endl
            << std::string() + "\"quaternion_x\":"  << (quaternion_x) << "," << std::endl
            << std::string() + "\"quaternion_y\":"  << (quaternion_y) << "," << std::endl
            << std::string() + "\"quaternion_z\":"  << (quaternion_z) << "," << std::endl
            << std::string() + "\"quaternion_w\":"  << (quaternion_w) << "," << std::endl
            << std::string() + "\"raw_acceleration_x\":"  << (raw_acceleration_x) << "," << std::endl
            << std::string() + "\"raw_acceleration_y\":"  << (raw_acceleration_y) << "," << std::endl
            << std::string() + "\"raw_acceleration_z\":"  << (raw_acceleration_z) << "," << std::endl
            << std::string() + "\"linear_acceleration_x\":"  << (linear_acceleration_x) << "," << std::endl
            << std::string() + "\"linear_acceleration_y\":"  << (linear_acceleration_y) << "," << std::endl
            << std::string() + "\"linear_acceleration_z\":"  << (linear_acceleration_z) << "," << std::endl
            << std::string() + "\"gravity_x\":"  << (gravity_x) << "," << std::endl
            << std::string() + "\"gravity_y\":"  << (gravity_y) << "," << std::endl
            << std::string() + "\"gravity_z\":"  << (gravity_z) << "," << std::endl
            << std::string() + "\"magnetic_heading\":"  << (magnetic_heading) << "," << std::endl
            << std::string() + "\"true_heading\":"  << (true_heading) << "," << std::endl
            << std::string() + "\"heading_accuracy\":"  << (heading_accuracy) << "," << std::endl
            << std::string() + "\"magnetometer_x\":"  << (magnetometer_x) << "," << std::endl
            << std::string() + "\"magnetometer_y\":"  << (magnetometer_y) << "," << std::endl
            << std::string() + "\"magnetometer_z\":"  << (magnetometer_z) << "," << std::endl
            << std::string() + "\"magnetometer_data_valid\":"  << (magnetometer_data_valid) << std::endl
            << "}" << std::endl
            << std::endl;;
    }
    void print() {
        std::cout
            << "{" << std::endl
            << std::string() + "\"length\":" + std::to_string(length) + "," << std::endl
            << std::string() + "\"rotation_pitch\":" + std::to_string(rotation_pitch) + "," << std::endl
            << std::string() + "\"rotation_roll\":" + std::to_string(rotation_roll) + "," << std::endl
            << std::string() + "\"rotation_yaw\":" + std::to_string(rotation_yaw) + "," << std::endl
            << std::string() + "\"rotation_rate_x\":" + std::to_string(rotation_rate_x) + "," << std::endl
            << std::string() + "\"rotation_rate_y\":" + std::to_string(rotation_rate_y) + "," << std::endl
            << std::string() + "\"rotation_rate_z\":" + std::to_string(rotation_rate_z) + "," << std::endl
            << std::string() + "\"quaternion_x\":" + std::to_string(quaternion_x) + "," << std::endl
            << std::string() + "\"quaternion_y\":" + std::to_string(quaternion_y) + "," << std::endl
            << std::string() + "\"quaternion_z\":" + std::to_string(quaternion_z) + "," << std::endl
            << std::string() + "\"quaternion_w\":" + std::to_string(quaternion_w) + "," << std::endl
            << std::string() + "\"raw_acceleration_x\":" + std::to_string(raw_acceleration_x) + "," << std::endl
            << std::string() + "\"raw_acceleration_y\":" + std::to_string(raw_acceleration_y) + "," << std::endl
            << std::string() + "\"raw_acceleration_z\":" + std::to_string(raw_acceleration_z) + "," << std::endl
            << std::string() + "\"linear_acceleration_x\":" + std::to_string(linear_acceleration_x) + "," << std::endl
            << std::string() + "\"linear_acceleration_y\":" + std::to_string(linear_acceleration_y) + "," << std::endl
            << std::string() + "\"linear_acceleration_z\":" + std::to_string(linear_acceleration_z) + "," << std::endl
            << std::string() + "\"gravity_x\":" + std::to_string(gravity_x) + "," << std::endl
            << std::string() + "\"gravity_y\":" + std::to_string(gravity_y) + "," << std::endl
            << std::string() + "\"gravity_z\":" + std::to_string(gravity_z) + "," << std::endl
            << std::string() + "\"magnetic_heading\":" + std::to_string(magnetic_heading) + "," << std::endl
            << std::string() + "\"true_heading\":" + std::to_string(true_heading) + "," << std::endl
            << std::string() + "\"heading_accuracy\":" + std::to_string(heading_accuracy) + "," << std::endl
            << std::string() + "\"magnetometer_x\":" + std::to_string(magnetometer_x) + "," << std::endl
            << std::string() + "\"magnetometer_y\":" + std::to_string(magnetometer_y) + "," << std::endl
            << std::string() + "\"magnetometer_z\":" + std::to_string(magnetometer_z) + "," << std::endl
            << std::string() + "\"magnetometer_data_valid\":" + std::to_string(magnetometer_data_valid) << std::endl
            << "}" << std::endl;;
    }

    std::size_t hint_length() {
        constexpr std::size_t value_count  = 23;
        return value_count;
    }

    std::size_t hint_size() {
        constexpr std::size_t value_count  = 23;
        return sizeof(float) * value_count + 4;
    }
    bool set_sensor_value(void * data, std::size_t size) {
        std::int32_t * plength = static_cast<std::int32_t*>(data);
        std::uint8_t * bytes = static_cast<std::uint8_t*>(data);
        std::swap(bytes[0], bytes[3]);
        std::swap(bytes[1], bytes[2]);
        float * values = static_cast<float*>(data)+1;
        if (hint_length() != *plength) {
            return false;
        }
        if (data == nullptr)
            throw std::invalid_argument("data is nullptr");

        if (size != hint_size())
            throw std::invalid_argument("Unexpected length of array. Exactly " +
                                        std::to_string(hint_size()) + " bytes were expected.");
        for (int i = 0; i < hint_length(); ++i) {
            void* data_ = static_cast<void*>(values+i);
            std::uint8_t * bytes_ = static_cast<std::uint8_t*>(data_);
            std::swap(bytes_[0], bytes_[3]);
            std::swap(bytes_[1], bytes_[2]);
        }

        length = *plength;
        double x = values[0];
        double y = values[1];
        double z = values[2];
        double w = values[3];

        rotation_pitch = std::atan2(2 * (y * z + w * x), w * w - x * x - y * y + z * z);
        rotation_roll = std::atan2(2 * (x * y + w * z), w * w + x * x - y * y - z * z);
        rotation_yaw = std::sin(-2 * (x * z - w * y));

        quaternion_x = values[0];
        quaternion_y = values[1];
        quaternion_z = values[2];
        quaternion_w = values[3];

        rotation_rate_x = values[7];
        rotation_rate_y = values[8];
        rotation_rate_z = values[9];

        raw_acceleration_x = values[13];
        raw_acceleration_y = values[14];
        raw_acceleration_z = values[15];

        linear_acceleration_x = values[4];
        linear_acceleration_y = values[5];
        linear_acceleration_z = values[6];

        gravity_x = values[10];
        gravity_y = values[11];
        gravity_z = values[12];

        magnetic_heading = values[16];
        true_heading = values[17];
        heading_accuracy = values[18];

        magnetometer_x = values[19];
        magnetometer_y = values[20];
        magnetometer_z = values[21];
        magnetometer_data_valid = (int)values[22] == 1;
        return true;
    }
};


class server {
public:
    server(asio::io_service & io_service, const tcp::endpoint & endpoint)
        : m_io_service(io_service),
          m_acceptor(io_service, endpoint),
          m_socket(m_io_service),
          m_buffer(m_reading.hint_size()),
          m_greeting{0x42,0xfe,0xa7,0x23}
        {
            do_accept();
        }
    void do_write() {
        asio::async_write(m_socket,
                          asio::buffer(m_greeting.data(), m_greeting.size()),
                          [this](auto ec, auto length){
                              if (ec) {
                              }
                              this->do_read();
                          });
    }
    void do_read() {
        asio::async_read(m_socket,
                         asio::buffer(m_buffer.data(), m_reading.hint_size()),
                         [this](boost::system::error_code ec , auto length){
                             if (ec) {
                                 return;
                             }
                             m_reading.set_sensor_value(m_buffer.data(), m_reading.hint_size());
                             // m_reading.print();
                             this->do_read();
                         }
            );
    }
    void do_accept() {
        m_acceptor.async_accept(m_socket,
                                [this](auto ec) {
                                    if (ec) {
                                        return;
                                    }
                                    this->do_write();
                                });
        // m_acceptor.async_accept(
        //     [this](auto ec, auto socket) {
        //         // if (!ec) {
        //         //     m_socket = std::move(socket);
        //         //     this->do_read();
        //         // }
        //     });
    }
    std::array<std::uint8_t, 4> m_greeting;
    sensor_reading m_reading;
    std::vector<std::uint8_t> m_buffer;
    tcp::acceptor m_acceptor;
    asio::io_service & m_io_service;
    tcp::socket m_socket;
};

class sensor_reading_updater {
public:
    sensor_reading_updater(asio::io_service & io_service, const tcp::endpoint & endpoint)
        : m_io_service(io_service),
          m_acceptor(io_service, endpoint),
          m_socket(m_io_service),
          m_buffer(m_reading.hint_size()),
          m_greeting{0x42,0xfe,0xa7,0x23}
        {
            do_accept();
        }
    void do_write() {
        asio::async_write(m_socket,
                          asio::buffer(m_greeting.data(), m_greeting.size()),
                          [this](auto ec, auto length){
                              if (ec) {
                              }
                              this->do_read();
                          });
    }
    void do_read() {
        asio::async_read(m_socket,
                         asio::buffer(m_buffer.data(), m_reading.hint_size()),
                         [this](boost::system::error_code ec , auto length){
                             if (ec) {
                                 return;
                             }
                             m_reading.set_sensor_value(m_buffer.data(), m_reading.hint_size());
                             m_reading.print();
                             this->do_read();
                         }
            );
    }
    void do_accept() {
        m_acceptor.async_accept(m_socket,
                                [this](auto ec) {
                                    if (ec) {
                                        return;
                                    }
                                    this->do_write();
                                });
    }
    void update(sensor_reading &reading) {
        m_io_service.post(
            [&,this](){
                std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);
                if (lock.try_lock()){
                    reading = m_reading;
                    lock.unlock();
                }
                m_cv.notify_all();
            });
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [this]{return m_ready;});
        }
    }
    void close() {
        m_io_service.post([this](){m_socket.close();});
    }
    bool m_ready;
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::array<std::uint8_t, 4> m_greeting;
    sensor_reading m_reading;
    sensor_reading * m_preading;
    std::vector<std::uint8_t> m_buffer;
    tcp::acceptor m_acceptor;
    asio::io_service & m_io_service;
    tcp::socket m_socket;
};

int main(int argc, char ** argv) {
    try {
        boost::asio::io_service io_service;
        // tcp::resolver resolver(io_service);
        if (argc < 2)
            return 1;
        tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
        // server server_(io_service, endpoint);
        sensor_reading_updater updater(io_service, endpoint);
        std::thread t([&](){io_service.run();});

        sensor_reading reading;
        while (!io_service.stopped()) {
            updater.update(reading);
            reading.print();
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
