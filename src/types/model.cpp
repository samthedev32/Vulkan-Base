#include <types/model.hpp>

static Model load(std::string path) {
  FILE *f = fopen(path.c_str(), "r");

  if (!f)
    throw std::runtime_error("Failed to open Model File");

  Model model;

  std::vector<vec<3>> vertices;
  std::vector<vec<2>> texCoords;

  // Load Model
  char line[256];
  while (fgets(line, sizeof(line), f)) {
    char index[8];
    char data[sizeof(line) - sizeof(index) - 2];
    int c = sscanf(line, "%7s %[^\n]s", index, data);

    if (c == 2) {
      if (!strcmp(index, "v")) {
        vec<3> vertex;
        sscanf(data, "%f %f %f", &vertex->x, &vertex->y, &vertex->z);
        vertices.push_back(vertex);
      } else if (!strcmp(index, "vt")) {
        vec<2> texCoord;
        sscanf(data, "%f %f %*f", &texCoord->x, &texCoord->y);
        texCoords.push_back(texCoord);
      } else if (!strcmp(index, "f")) {
        int v[4], vt[4];
        char part[4][128];
        int parts =
            sscanf(data, "%s %s %s %s", part[0], part[1], part[2], part[3]);

        for (int i = 0; i < parts; i++) {
          if (sscanf(part[i], "%i/%i/%*i", &v[i], &vt[i]) != 3)
            if (sscanf(part[i], "%i//%*i", &v[i]) != 2)
              if (sscanf(part[i], "%i/%i", &v[i], &vt[i]) != 2)
                if (sscanf(part[i], "%i", &v[i]) != 1) {
                  printf("Failed to read Face Line\n");
                  parts = 0;
                }
        }

        if (parts != 3)
          printf("Face is not a Tri (%i)\n", parts);
        else {
          // TODO: duplicate face optimization
          for (int i = 0; i < 3; i++) {
            Vertex vertex;
            vertex.position = vertices[v[i] - 1];
            if (texCoords.size() > vt[i])
              vertex.texCoord = texCoords[vt[i] - 1];

            model.vertices.push_back(vertex);
            model.indices.push_back(model.vertices.size() - 1);
          }
        }
      }
    }
  }

  if (model.indices.size() < 3)
    throw std::runtime_error("No Triangles were loaded");

  // model.vertices = {{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
  //                   {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
  //                   {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
  //                   {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}};

  // model.indices = {0, 1, 2, 2, 3, 0};

  return model;
}