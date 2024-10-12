import { annotate } from "rough-notation";
import { RoughAnnotationConfig } from "rough-notation/lib/model";

const mainHeading = document.querySelector("h1") as HTMLElement;
const helpHeading = document.querySelector("h2.help") as HTMLElement;

const annotationConfig: RoughAnnotationConfig = {
    type: "underline",
    color: "blanchedalmond",
    padding: [10, 10],
    strokeWidth: 3,
    iterations: 2,
};

const annotation = annotate(mainHeading, annotationConfig);
const helpAnnotation = annotate(helpHeading, annotationConfig);

annotation.show();
helpAnnotation.show();
