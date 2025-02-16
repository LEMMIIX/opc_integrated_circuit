# opC++ Integrated Circuit

The opC++ integrated circuit (IC) is a training project build up on a fantasy circuit. It encompasses the brain IC (opcpp ic), a database and a series of sensors as shown in the figure:<br>
!["circuit](/img/opc_ic_circuit.png)<br>
<br>
TASKS<br>
Using the API, the static object library (for windows), and the datasheet (opcpp_IC.pdf), build up an application software around it such that:
<br>
1. powers up the circuit and provides access to the current state via a global const bool& system_is_powered_up
2. reads calibrations and sets up all the sensors
3. makes sensor reads
4. makes IC registry read/write operations
5. conducts IC tests (test mode/jtag mode)

# Project documentation

Git branches have this format:<br>
`category/MAJOR-MINOR-PATCH`<br>
For example: `feature/1.4.9` is a `feature` branch which of major version `1` which includes the minor sub version `4` and is the `9`th patch release.<br>
Release versions follow the same format.
Versioning is lightly based on SemVer [semantic versioning](https://semver.org)<br>