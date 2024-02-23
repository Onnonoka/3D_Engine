#include <Object3D/Object3D.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Error/EngineError.hpp>
#include <iostream>
#include <algorithm>

Object3D::Object3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : BasicObject(position, rotation, scale) { }

Object3D::~Object3D() {
    clearBuffers();
}

GLuint Object3D::getVAO() const {
    return VAO;
}

void Object3D::createGLBuffer() {
    // Create VAO, VBO and EBO
    glCreateBuffers(1, &EBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCreateBuffers(1, &VBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCreateVertexArrays(1, &VAO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Put data in element buffers
    glNamedBufferData(VBO, geometry.getArrayBufferDataSize(), geometry.getArrayBufferData().data(), GL_STATIC_DRAW);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    glNamedBufferData(EBO, geometry.getIndexBufferDataSize(), geometry.getIndexBufferData().data(), GL_STATIC_DRAW);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Binding element buffers to VAO
    glEnableVertexArrayAttrib(VAO, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glVertexArrayAttribBinding(VAO, 0, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(glm::vec3));
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    // Material *mat = getMaterial();
    // GLuint materialVBO = mat->getVBO();
    // if (glIsBuffer(materialVBO)) {
    //     glEnableVertexArrayAttrib(VAOid, 1);
    //     glVertexArrayAttribBinding(VAOid, 1, 0);
    //     CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    //     glVertexArrayVertexBuffer(VAOid, 1, materialVBO, 0, sizeof(Color));
    //     CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    // }
    glVertexArrayElementBuffer(VAO, EBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void Object3D::clearBuffers() {
    glDeleteBuffers(1, &VBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glDeleteBuffers(1, &EBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glDeleteVertexArrays(1, &VAO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void Object3D::setGeometry(Geometry newGeometry) {
    geometry = newGeometry;
}

Geometry Object3D::getGeometry() const {
    return geometry;
}
