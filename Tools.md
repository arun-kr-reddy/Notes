# Tools
- [Mermaid](#mermaid)
  - [Flowchart](#flowchart)
  - [Sequence Diagram](#sequence-diagram)
  - [Gantt Diagram](#gantt-diagram)
  - [Class Diagram](#class-diagram)
  - [Git Graph](#git-graph)
  - [Quadrant Chart](#quadrant-chart)
  - [X-Y Chart](#x-y-chart)
- [Powershell](#powershell)
- [Local LLM](#local-llm)

## Links <!-- omit from toc -->

## To Do <!-- omit from toc -->

## Mermaid
- [Documentation](https://mermaid.js.org/intro/)

### Flowchart
- **Node Shapes:**
  |               |               |              |
  | ------------- | ------------- | ------------ |
  | oval          | `id1((text))` | start/end    |
  | parallelogram | `id1[/text/]` | input/output |
  | rectangle     | `id1[text]`   | process node |
  | diamond       | `id1{text}`   | decision     |
- ```text
  graph LR
    a((start))
    b[func1]
    c[func2]
    d[/input/]
    e{cond}
    f((end))

    a --> b
    b --> e
    c --> f
    e -- no --> f

    %% all nodes used in subgraph grouped together
    subgraph process
    e -- yes --> c
    d -. copy .-> c
    end
  ```
  ```mermaid
  graph LR
    a((start))
    b[func1]
    c[func2]
    d[/input/]
    e{cond}
    f((end))

    a --> b
    b --> e
    c --> f
    e -- no --> f

    subgraph subgroup
    e -- yes --> c
    d -. copy .-> c
    end
  ```

### Sequence Diagram
- ```text
  %% participants rendered in order of declaration
  sequenceDiagram
    title example sequence diagram
    autonumber  %% to auto-generate sequence numbers
    participant t1 as thread1
    participant t2 as thread2
    participant t3 as thread3

    %% activation period by appending + & - to connection
    t1 ->>+ t2: frame_start

    loop busy_wait
      t2 -->> t3: reg_read
      t3 -->> t2: reg_val
    end

    alt if_flag
      t2 -->> t2: post_process
    end

    par core1
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    and core2
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    end

    note over t1, t2: some comment
    t2 ->>- t1: frame_done
  ```
  ```mermaid
  sequenceDiagram
    title example sequence diagram
    autonumber
    participant t1 as thread1
    participant t2 as thread2
    participant t3 as thread3

    t1 ->>+ t2: frame_start

    loop busy_wait
      t2 -->> t3: reg_read
      t3 -->> t2: reg_val
    end

    alt if_flag
      t2 -->> t2: post_process
    end

    par core1
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    and core2
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    end

    note over t1, t2: some comment
    t2 ->>- t1: frame_done
  ```

### Gantt Diagram
- ```text
  gantt
    dateFormat YYYY-MM-DD
    title example gantt diagram
    excludes weekends

    section sectionA
      start : milestone, start, 2025-01-01, 0d
      task1 : done, t1, after start, 2d
      task2 : active, t2, after t1, 3d
      task3 : t3, after t2, 5d

    section sectionB
      task5 : crit, t4, after t3, 2d
      task6 : t5, after t4, 3d
      end : milestone, after t5, 0d
  ```
  ```mermaid
  gantt
    dateFormat YYYY-MM-DD
    title example gantt diagram
    excludes weekends

    section sectionA
      start : milestone, start, 2025-01-01, 0d
      task1 : done, t1, after start, 2d
      task2 : active, t2, after t1, 3d
      task3 : t3, after t2, 5d

    section sectionB
      task5 : crit, t4, after t3, 2d
      task6 : t5, after t4, 3d
      end : milestone, after t5, 0d
  ```

### Class Diagram
- **Relations:**
  |            |                   |
  | ---------- | ----------------- |
  | `<\|--`    | inheritance       |
  | `*--`      | composition       |
  | `o--`      | aggregation       |
  | `-->`      | association       |
  | `---`      | link              |
  | `..>`      | dependency        |
  | `..>`      | realization       |
  | `<\|--\|>` | two-way relations |
- ```text
  classDiagram
    namespace BaseShapes {
      class Shapes{
        <<interface>>
        +area(Shapes) int
      }
      class Square{
          %% variables
          +int length
          %% method with arguments & return value
          +area(Square) int
      }
      class Rectangle{
          +int length
          +int breadth
          +area(Rectangle) int
      }
      class Circle{
          +int radius
          +area(Circle) float
          +circumference(Circle) float
      }
      class Random{
        +List~int~ points
        +area(List~int~ points) int
      }
    }

    Shapes <|-- Circle
    Shapes <|-- Rectangle
    Rectangle <|-- Square : parent
    Shapes <|-- Random

    note for Circle "defined in /shapes/circle.hpp"
  ```
  ```mermaid
  classDiagram
    namespace BaseShapes {
      class Shapes{
        <<interface>>
        +area(Shapes) int
      }
      class Square{
          %% variables
          +int length
          %% method with arguments & return value
          +area(Square) int
      }
      class Rectangle{
          +int length
          +int breadth
          +area(Rectangle) int
      }
      class Circle{
          +int radius
          +area(Circle) float
          +circumference(Circle) float
      }
      class Random{
        +List~int~ points
        +area(List~int~ points) int
      }
    }

    Shapes <|-- Circle
    Shapes <|-- Rectangle
    Rectangle <|-- Square : parent
    Shapes <|-- Random

    note for Circle "defined in /shapes/circle.hpp"
  ```

### Git Graph
- ```text
  gitGraph LR:
    title example git graph
    commit id: "commit1"
    commit id: "commit2"
    branch develop
    checkout develop
    commit id: "commit3"
    commit id: "reverse commit3" type: REVERSE
    commit id: "commit4"
    checkout main
    merge develop
    commit id: "commit5" type: HIGHLIGHT tag:"v1.0"
    commit id: "commit6"
  ```
  ```mermaid
  gitGraph LR:
    title example git graph
    commit id: "commit1"
    commit id: "commit2"
    branch develop
    checkout develop
    commit id: "commit3"
    commit id: "reverse commit3" type: REVERSE
    commit id: "commit4"
    checkout main
    merge develop
    commit id: "commit5" type: HIGHLIGHT tag:"v1.0"
    commit id: "commit6"
  ```

### Quadrant Chart
- ```text
  quadrantChart
    title example quadrant chart
    x-axis low talent --> high talent
    y-axis low agency --> high agency
    quadrant-1 game changers
    quadrant-2 go-getters
    quadrant-3 cogs in wheel
    quadrant-4 frustated geniuses

    %% without points, quadrant titles in the centre
    candidate_1: [0.3, 0.6]
    candidate_2: [0.45, 0.23]
    candidate_3: [0.57, 0.69]
    candidate_4: [0.78, 0.34]
    candidate_5: [0.40, 0.34]
    candidate_6: [0.35, 0.78]
  ```
  ```mermaid
  quadrantChart
    title example quadrant chart
    x-axis low talent --> high talent
    y-axis low agency --> high agency
    quadrant-1 game changers
    quadrant-2 go-getters
    quadrant-3 cogs in wheel
    quadrant-4 frustated geniuses

    candidate_1: [0.3, 0.6]
    candidate_2: [0.45, 0.23]
    candidate_3: [0.57, 0.69]
    candidate_4: [0.78, 0.34]
    candidate_5: [0.40, 0.34]
    candidate_6: [0.35, 0.78]
  ```

### X-Y Chart
- ```text
  ---
  config:
    themeVariables:
      xyChart:
        plotColorPalette: '#000000, #FF0000, #00FF00'
  ---
  xychart-beta
    title "example X-Y chart"
    x-axis [jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]
    y-axis "savings (in ₹)" 0 --> 10000000
    bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [20000, 100000, 400000, 2000000, 3000000, 5000000, 6000000, 7000000, 10000000, 12000000, 16000000, 18000000]
  ```
  ```mermaid
  ---
  config:
    themeVariables:
      xyChart:
        plotColorPalette: '#000000, #FF0000, #00FF00'
  ---
  xychart-beta
    title "example X-Y chart"
    x-axis [jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]
    y-axis "savings (in ₹)" 0 --> 10000000
    bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [20000, 100000, 400000, 2000000, 3000000, 5000000, 6000000, 7000000, 10000000, 12000000, 16000000, 18000000]
  ```

## Powershell
- **Filename String Replace:**
  ```bash
  get-childitem * | foreach { rename-item $_ $_.Name.Replace("Lecture ","") }
  ```

## Local LLM
- **llama.cpp:**
  - install using `winget install --id=ggml.llamacpp --exact --silent`
  - install [continue.dev](https://marketplace.visualstudio.com/items?itemName=Continue.continue) VS-Code extension
  - add below to `C:\Users\arun\.continue\config.yaml`
    ```yaml
    models:
      - name: llama.cpp
        provider: llama.cpp
        model: llama.cpp
        apiBase: http://localhost:8080
    ```
  - download model (GGUF version) from [Hugging Face](https://huggingface.co/models?num_parameters=min:0,max:6B&library=gguf&sort=downloads)
  - trigger llama.cpp server then use it in VS-Code
    ```bash
    llama-server -m <path_to_model>
    ```