<?php

use Tracy\IBarPanel;
use Tracy\Dumper;

/**
 * Custom PW panel
 */

class VariablesPanel implements IBarPanel {
    public function getTab() {
        return '
        <style>
            .tracy-panel {
                max-height: 90% !important;
                max-width: 95% !important;
                overflow-y: scroll !important;
            }
        </style>
        <span title="Variables">
            <svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" x="0px" y="0px" viewBox="0 0 492 492" style="enable-background:new 0 0 492 492;" xml:space="preserve" width="16px" height="16px">
                <path d="M370.5,254c-14.667-11.333-36.667-20.667-66-28l-23-5v-97c0.667,0.667,1.333,1,2,1s1,0.333,1,1    c19.334,9.333,29.668,25.333,31,48h77c-1.333-40-16.333-70.667-45-92c-18.667-14-40.667-23.333-66-28V0h-71v52    c-33.333,4-59.667,14.667-79,32c-25.333,22.667-38,51.334-38,86c0,37.333,13,65,39,83c14,10,40,19.333,78,28v104    c-14-4-24.667-10.333-32-19c-8-9.333-13-22-15-38h-76c0,39.333,14.333,70.333,43,93c20.667,16,47.333,26.333,80,31v40h71v-39    c34.667-4.667,62.333-15.667,83-33c26.667-23.333,40-52.667,40-88C404.5,298,393.167,272,370.5,254z M210.5,204    c-11.333-3.333-19.333-6.333-24-9c-12.667-6.667-19-17-19-31c0-15.333,6.333-27,19-35c6.667-4,14.667-7.333,24-10V204z M293.5,383    c-3.333,1.333-7.333,2.333-12,3v-89c12.667,4,22.333,8,29,12c11.333,7.333,17,17.333,17,30C327.5,360.333,316.167,375,293.5,383z" fill="#444444"/>
            </svg>Variables
        </span>
        ';
    }



    public function getPanel() {

        // panel title
        $out = '
        <h1>
            <svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" x="0px" y="0px" viewBox="0 0 492 492" style="enable-background:new 0 0 492 492;" xml:space="preserve" width="16px" height="16px">
                <path d="M370.5,254c-14.667-11.333-36.667-20.667-66-28l-23-5v-97c0.667,0.667,1.333,1,2,1s1,0.333,1,1    c19.334,9.333,29.668,25.333,31,48h77c-1.333-40-16.333-70.667-45-92c-18.667-14-40.667-23.333-66-28V0h-71v52    c-33.333,4-59.667,14.667-79,32c-25.333,22.667-38,51.334-38,86c0,37.333,13,65,39,83c14,10,40,19.333,78,28v104    c-14-4-24.667-10.333-32-19c-8-9.333-13-22-15-38h-76c0,39.333,14.333,70.333,43,93c20.667,16,47.333,26.333,80,31v40h71v-39    c34.667-4.667,62.333-15.667,83-33c26.667-23.333,40-52.667,40-88C404.5,298,393.167,272,370.5,254z M210.5,204    c-11.333-3.333-19.333-6.333-24-9c-12.667-6.667-19-17-19-31c0-15.333,6.333-27,19-35c6.667-4,14.667-7.333,24-10V204z M293.5,383    c-3.333,1.333-7.333,2.333-12,3v-89c12.667,4,22.333,8,29,12c11.333,7.333,17,17.333,17,30C327.5,360.333,316.167,375,293.5,383z" fill="#444444"/>
            </svg>
            Non-ProcessWire Template Variables
        </h1>
        <p>These are all the non-PW variables that are available in the template for this page.</p>
        <p>If you are looking for the page fields and their values, look in the ProcessWire panel under "Page Field Values"</p>
        <br >
        ';

        $templateFilename = wire('page')->template->filename;
        $targetData = file_get_contents($templateFilename);
        //check to see if template can be compiled because we need that to get the variables
        //the missing "F" in "ileCompiler=0" is an intentional hack - otherwise it prevents this file from being compiled and creates
        //missing wire function errors
        if(wire('config')->version < 3) {
            $out .= '<strong>This feature only works with PW 3+</strong>';
        }
        elseif(wire('page')->template->compile != 0 && wire('config')->templateCompile !== false && stripos($targetData, "ileCompiler=0") === false) {
            $out .= TD::dump(wire('templateVars'), array(Dumper::COLLAPSE => false));
        }
        else {
            $out .= '<strong>This template could not be compiled, so the variables could not be determined.</strong>';
        }

        return $out;
    }

}