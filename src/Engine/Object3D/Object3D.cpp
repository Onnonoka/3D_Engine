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

void Object3D::createGLBuffers() {
    // Create VAO, VBO and EBO
    glCreateBuffers(1, &EBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCreateBuffers(1, &VBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCreateBuffers(1, &CBO);
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

    if (glIsBuffer(CBO)) {
        glNamedBufferData(CBO, material.getMaterialBufferDataSize(), material.getMaterialBufferData().data(), GL_STATIC_DRAW);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

        glEnableVertexArrayAttrib(VAO, 1);
        glVertexArrayAttribBinding(VAO, 1, 1);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        
        glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

        glVertexArrayVertexBuffer(VAO, 1, CBO, 0, sizeof(Color));
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    }
    glVertexArrayElementBuffer(VAO, EBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void Object3D::clearBuffers() {
    glDeleteBuffers(1, &VBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glDeleteBuffers(1, &EBO);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glDeleteBuffers(1, &CBO);
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

Material Object3D::getMaterial()const {
    return material;
}

void Object3D::setMaterial(const Material newMaterial) {
    material = newMaterial;
}

void Object3D::updateGLBuffers() {

    if (!glIsBuffer(VAO)) {
        // Create the VAO
        glCreateVertexArrays(1, &VAO);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    }

    if (geometry.isDirty(Geometry::VERTICES)) {
        if (!glIsBuffer(VBO)) {
            // Create the VBO
            glCreateBuffers(1, &VBO);
            CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        }
        // Put data in vertex buffers
        glNamedBufferData(VBO, geometry.getArrayBufferDataSize(), geometry.getArrayBufferData().data(), GL_STATIC_DRAW);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

        // Binding vertex buffer to VAO
        glEnableVertexArrayAttrib(VAO, 0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glVertexArrayAttribBinding(VAO, 0, 0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(glm::vec3));
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    }

    if (material.isDirty(Material::COLOR) || geometry.isDirty(Geometry::VERTICES)) {
        if (!glIsBuffer(CBO)) {
            // Create the VBO
            glCreateBuffers(1, &CBO);
            CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        }
        std::cout << "IN UPDATE CBO" << std::endl;
        material.updateMaterialbufferData(geometry.getArrayBufferData());
        // Put data in element buffers
        glNamedBufferData(CBO, material.getMaterialBufferDataSize(), material.getMaterialBufferData().data(), GL_STATIC_DRAW);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        
        // Binding color buffer to VAO
        glEnableVertexArrayAttrib(VAO, 1);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glVertexArrayAttribBinding(VAO, 1, 1);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glVertexArrayVertexBuffer(VAO, 1, CBO, 0, sizeof(Color));
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    }
    
    if (geometry.isDirty(Geometry::INDICES)) {
        if (!glIsBuffer(EBO)) {
            // Create the VBO
            glCreateBuffers(1, &EBO);
            CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        }
        // Put data in element buffers
        glNamedBufferData(EBO, geometry.getIndexBufferDataSize(), geometry.getIndexBufferData().data(), GL_STATIC_DRAW);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        
        // Binding element buffer to VAO
        glVertexArrayElementBuffer(VAO, EBO);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    }

    geometry.clean();
    material.clean();
}
