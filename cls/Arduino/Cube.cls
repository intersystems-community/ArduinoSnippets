/// Класс с данными с платы
Class Arduino.Cube Extends %DeepSee.CubeDefinition [ DependsOn = Arduino.Info, ProcedureBlock ]
{

Parameter DOMAIN;

/// Cube definition from Architect.
XData Cube [ XMLNamespace = "http://www.intersystems.com/deepsee" ]
{
<cube xmlns="http://www.intersystems.com/deepsee" name="Arduino" displayName="Arduino" description="Класс с данными с платы" disabled="false" abstract="false" sourceClass="Arduino.Info" countMeasureName="%COUNT" bucketSize="8" bitmapChunkInMemory="false" precompute="0">
  <dimension name="Время измерения" disabled="false" hasAll="false" allCaption="All DateTime" allDisplayName="DateTime" sourceProperty="DateTime" type="time" iKnowType="entity" hidden="false" showHierarchies="default">
    <hierarchy name="H1" disabled="false">
      <level name="DateTime" displayName="Дата" disabled="false" timeFunction="DayMonthYear" list="false" useDisplayValue="true" useAsFilter="true">
      </level>
      <level name="Hour" displayName="Часы" disabled="false" timeFunction="HourNumber" list="false" useDisplayValue="true" useAsFilter="true">
      </level>
      <level name="Minute" displayName="Минуты" disabled="false" timeFunction="MinuteNumber" list="false" useDisplayValue="true" useAsFilter="true">
      </level>
    </hierarchy>
  </dimension>
  <measure sourceProperty="Brightness" name="Brightness" displayName="Яркость" disabled="false" aggregate="AVG" type="number" hidden="false" searchable="false" iKnowSource="string"></measure>
  <measure sourceProperty="Temperature" name="Temperature" displayName="Температура, C" disabled="false" aggregate="AVG" type="number" hidden="false" searchable="false" iKnowSource="string"></measure>
  <measure sourceProperty="Humidity" name="Humidity" displayName="Влажность, %" disabled="false" aggregate="AVG" type="number" hidden="false" searchable="false" iKnowSource="string"></measure>
</cube>
}

}

