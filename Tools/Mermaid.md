# Mermaid
- [Flowchart](#flowchart)
- [Sequence Diagram](#sequence-diagram)
- [Gantt Diagram](#gantt-diagram)
- [Class Diagram](#class-diagram)
- [Git Graph](#git-graph)
- [Quadrant Chart](#quadrant-chart)
- [X-Y Chart](#x-y-chart)

## Links <!-- omit from toc -->
- [Mermaid Documentation](https://mermaid.js.org/intro/)

## Flowchart
- **Node Shapes:**
  |               |               |              |
  | ------------- | ------------- | ------------ |
  | oval          | `id1([text])` | start/end    |
  | parallelogram | `id1[/text/]` | input/output |
  | rectangle     | `id1[text]`   | process node |
  | diamond       | `id1{text}`   | decision     |
- ㅤ
  ```mermaid
  graph LR
      Start([START]) --> Process1[Pre-Proc]
      Process1 --> Decision{Condition}

      subgraph Main Process
          Decision -- YES --> Process2[Compute]
          Input[/Input/] -. COPY .-> Process2
      end

      Decision -- NO --> End([END])
      Process2 --> End
  ```

## Sequence Diagram
- ㅤ
  ```mermaid
  sequenceDiagram
      title Example Sequence Diagram
      autonumber

      participant t1 as Thread 1
      participant t2 as Thread 2
      participant t3 as Thread 3

      %% '+' activates the receiver lifeline
      t1 ->>+ t2: frame_start

      loop busy_wait
          t2 -->> t3: reg_read
          t3 -->> t2: reg_val
      end

      %% 'alt' block for explicit if / else conditions
      alt if_true
          t2 -->> t2: pre_process_1
      else if_false
          t2 -->> t2: pre_process_2
      end

      %% Parallel execution block
      par core1
          t2 ->> t3: frame_a
          t3 -->> t2: output_a
      and core2
          t2 ->> t3: frame_b
          t3 -->> t2: output_b
      end

      note over t1, t2: Synchronization point
      %% '-' deactivates the sender lifeline
      t2 ->>- t1: frame_done
  ```

## Gantt Diagram
- ㅤ
  ```mermaid
  gantt
      dateFormat  YYYY-MM-DD
      title       Example Gantt Diagram
      excludes    weekends

      section Planning Phase
          Start Milestone : milestone, start_id, 2026-06-01, 0d
          Task 1          : done, t1, after start_id, 30d
          Task 2          : active, t2, after t1, 21d
          Task 3          : t3, after t2, 25d

      section Execution Phase
          Critical Task   : crit, t4, after t3, 55d
          Final Task      : t5, after t4, 35d
          End Milestone   : milestone, end_id, after t5, 0d
  ```

## Class Diagram
- **Relations:**
  |                            |         |                       |
  | -------------------------- | ------- | --------------------- |
  | solid line, closed arrow   | `<\|--` | inheritance           |
  | dotted line, closed arrow  | `..\|>` | interface realization |
  | solid line, filled diamond | `*--`   | composition           |
  | solid line, open diamond   | `o--`   | aggregation           |
  | solid line, open arrow     | `-->`   | association           |
  | dotted line, open arrow    | `..>`   | dependency            |
- ㅤ
  ```mermaid
  classDiagram
      namespace BaseShapes {
          class Shape {
              <<interface>>
              +area() int
          }
          class Square {
              +int length
              +area() int
          }
          class Rectangle {
              +int length
              +int breadth
              +area() int
          }
          class CustomPolygon {
              +int[] points
              +area(int[] points) int
          }
      }

      %% Interface Realization (Dotted)
      Shape <|.. CustomPolygon

      %% Inheritance (Solid)
      Shape <|-- Rectangle
      Rectangle <|-- Square : extends

      note for Shape "shape interface that actual shapes inherit"
  ```

## Git Graph
- ㅤ
  ```mermaid
  gitGraph
      title Example Git Graph
      commit id: "commit1"
      commit id: "commit2"

      branch develop
      checkout develop
      commit id: "commit3"
      commit id: "reverse commit3" type: REVERSE
      commit id: "commit4"

      checkout main
      merge develop
      commit id: "commit5" type: HIGHLIGHT tag: "v1.0"
      commit id: "commit6"
  ```

## Quadrant Chart
- ㅤ
  ```mermaid
  quadrantChart
      title Talent vs Agency Matrix
      x-axis Low Talent --> High Talent
      y-axis Low Agency --> High Agency
      quadrant-1 Game Changers
      quadrant-2 Go-Getters
      quadrant-3 Cogs in the Wheel
      quadrant-4 Frustrated Geniuses

      candidate_1: [0.3, 0.6]
      candidate_2: [0.45, 0.23]
      candidate_3: [0.57, 0.69]
      candidate_4: [0.78, 0.34]
      candidate_5: [0.40, 0.34]
      candidate_6: [0.35, 0.78]
  ```

## X-Y Chart
- ㅤ
  ```mermaid
  ---
  config:
    themeVariables:
      xyChart:
        plotColorPalette: '#000000, #FF0000, #00FF00'
  ---
  xychart-beta
      title "Example X-Y Chart"
      x-axis ["jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"]
      y-axis "Savings (in ₹)" 0 --> 20000000
      bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
      line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
      line [20000, 100000, 400000, 2000000, 3000000, 5000000, 6000000, 7000000, 10000000, 12000000, 16000000, 18000000]
  ```