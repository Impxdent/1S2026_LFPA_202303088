## Diagrama de Flujo del Sistema

```mermaid
flowchart TD
    A[Inicio del programa] --> B[Mostrar menú principal]

    B --> C{Opción seleccionada}

    C -->|1| D[Cargar archivo de estudiantes]
    D --> B

    C -->|2| E[Cargar archivo de cursos]
    E --> B

    C -->|3| F[Cargar archivo de notas]
    F --> B

    C -->|4| G[Generar reporte estadísticas por curso]
    G --> B

    C -->|5| H[Generar reporte rendimiento por estudiante]
    H --> B

    C -->|6| I[Generar reporte Top 10 estudiantes]
    I --> B

    C -->|7| J[Generar reporte cursos con mayor reprobación]
    J --> B

    C -->|8| K[Generar reporte análisis por carrera]
    K --> B

    C -->|9| L[Finalizar programa]
    L --> M[Fin]
