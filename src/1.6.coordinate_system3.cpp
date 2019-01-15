#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;
// using namespace glbinding;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "1.3.shader.hpp"
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <boost/asio.hpp>

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
                             {
                                std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);
                                if (lock.try_lock()){
                                    m_reading.set_sensor_value(m_buffer.data(), m_reading.hint_size());
                                    m_reading.print();
                                    lock.unlock();
                                }
                             }
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
    void try_update(sensor_reading &reading) {
        {
            std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);
            if (lock.try_lock()){
                reading = m_reading;
                lock.unlock();
            }
        }
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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char *vertexShaderSourcePath =
    "./1.6.coordinate_system2-vertex.glsl";
const char *fragmentShaderSourcePath =
    "./1.6.coordinate_system2-fragment.glsl";

class renderer {
public:
    unsigned int m_texture1;
    unsigned int m_texture2;
    unsigned int m_texture3;
    int m_width1;
    int m_height1;
    int m_channel1;
    int m_width2;
    int m_height2;
    int m_channel2;
    int m_width3;
    int m_height3;
    int m_channel3;
    std::shared_ptr<Shader> m_program;
    unsigned int VBO, VAO, EBO;
    void setup() {
        setup_shader();
        setup_vertices();
        setup_texture();
    }
    void setup_shader() {
        // build and compile our shader zprogram
        // ------------------------------------
        m_program = std::make_shared<Shader>(vertexShaderSourcePath, fragmentShaderSourcePath);
    }
    void setup_texture() {
        setup_texture1();
        setup_texture2();
        setup_texture3();
        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        m_program->use();
        m_program->setInt("texture1",0);
        m_program->setInt("texture2",1);
        m_program->setInt("texture3",2);
    }
    void setup_vertices() {
        float vertices[] = {

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2.f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 2.f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 2.f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 2.f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 2.f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2.f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0

        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        // texture coord attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LESS);
    }
    void setup_texture1() {
        glGenTextures(1, &m_texture1);
        glBindTexture(GL_TEXTURE_2D, m_texture1);
        // set the m_texture wrapping/filtering options (on the currently bound texture object)
        // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the m_texture
        // unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channel, 0);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("grass_side.png", &m_width1, &m_height1, &m_channel1, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width1, m_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    void setup_texture2() {
        glGenTextures(1, &m_texture2);
        glBindTexture(GL_TEXTURE_2D, m_texture2);
        // set the m_texture wrapping/filtering options (on the currently bound texture object)
        // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the m_texture
        // unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channel, 0);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("grass_path_top.png", &m_width2, &m_height2, &m_channel2, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width2, m_height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    void setup_texture3() {
        glGenTextures(1, &m_texture3);
        glBindTexture(GL_TEXTURE_2D, m_texture3);
        // set the m_texture wrapping/filtering options (on the currently bound texture object)
        // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the m_texture
        // unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channel, 0);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("dirt.png", &m_width3, &m_height3, &m_channel3, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width3, m_height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    void render(sensor_reading * preading = nullptr) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_texture3);

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        if (!preading) {
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        } else {
            glm::quat q;
            q.x = preading->quaternion_x;
            q.y = preading->quaternion_y;
            q.z = preading->quaternion_z;
            q.w = preading->quaternion_w;
            glm::mat4 m = glm::mat4_cast(q);
            model = m * model;
        }
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(m_program->id(), "model");
        unsigned int viewLoc  = glGetUniformLocation(m_program->id(), "view");
        unsigned int projectionLoc  = glGetUniformLocation(m_program->id(), "projection");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        // m.setMat4("projection", projection);

        // render box
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
    void teardown() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        // glDeleteBuffers(1, &EBO);
    }
};

class window {};

int main(int argc, char** argv)
{
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
        // while (!io_service.stopped()) {
        //     updater.update(reading);
        //     reading.print();
        // }

        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glbinding: load all OpenGL function pointers
        // ---------------------------------------
        glbinding::Binding::initialize(glfwGetProcAddress);

        // build and compile our shader program
        // ------------------------------------
        renderer renderer_;
        renderer_.setup();

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            // render
            // ------
            updater.try_update(reading);
            // renderer_.render(&reading);
            renderer_.render(&reading);
            reading.print();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        updater.close();
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        // glDeleteVertexArrays(1, &VAO);
        // glDeleteBuffers(1, &VBO);
        renderer_.teardown();

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------

        glfwTerminate();

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
