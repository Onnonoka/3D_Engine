#include <Object3D/Object3D.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Error/EngineError.hpp>
#include <glm/gtc/type_ptr.hpp>
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

void Object3D::setGeometry(const Geometry newGeometry) {
    geometry = newGeometry;
}

Geometry& Object3D::getGeometry() {
    return geometry;
}

Material& Object3D::getMaterial() {
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
        material.updateMaterialBufferData(geometry.getArrayBufferData());
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

    geometry.cleanDirtyFlags();
    material.cleanDirtyFlags();
}

bool Object3D::operator==(const Object3D& other) const {
    // Comparez les membres de l'objet un par un
    return (
        getPosition() == other.getPosition() &&
        getRotation() == other.getRotation() &&
        getScale() == other.getScale() &&
        geometry == other.geometry &&
        material == other.material
    );
}

void Object3D::render(const Camera& camera, const glm::mat4 parentModelMatrix, const GLuint shaderProgram) {
    updateGLBuffers();
    glm::mat4 global_transform = parentModelMatrix * getTransformationMatrix();

    glUseProgram(shaderProgram);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR, {std::to_string(static_cast<unsigned int>(shaderProgram))});

    glBindVertexArray(getVAO());
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    GLuint transformMatrixLocation = glGetUniformLocation(shaderProgram, "transform");
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, glm::value_ptr(global_transform));
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(getGeometry().getNumberOfFaces()), GL_UNSIGNED_INT, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    glBindVertexArray(0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}
